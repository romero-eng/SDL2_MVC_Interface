import re
import shutil
import traceback
import subprocess
from pathlib import Path
from os.path import commonpath


def mapping_to_string(mapping_title: str,
                      mapping: dict[str, str]) -> str:

    max_key_length: int = max([len(key) for key in mapping])
    return f'\n{mapping_title:s}:\n{'':{'-':s}>{len(mapping_title) + 1:d}s}\n{'\n'.join([f'  {key:>{max_key_length:d}s}: {value:s}' for key, value in mapping.items()]):s}\n'  # noqa: E231, E501


def run_shell_command(description: str,
                      command: str,
                      shell_path: Path = Path.cwd(),
                      successful_return_code: int = 0) -> None:

    shell_results: subprocess.CompletedProcess[bytes] = \
        subprocess.run(command,
                       stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE,
                       cwd=shell_path,
                       shell=True)

    command_results: dict[str, str] = \
        {'Directory': str(shell_path),
           'command': command}             # noqa: E127

    if shell_results.stdout:
        command_results['Output'] = f'\n\n{'\n'.join([f'{line:s}' for line in shell_results.stdout.decode('utf-8').split('\n')]):s}'  # noqa: E501

    if shell_results.stderr:
        command_results['Error'] = f'\n\n{'\n'.join([f'{line:s}' for line in shell_results.stderr.decode('utf-8').split('\n')]):s}'  # noqa: E501

    printable_shell_results: str = \
        mapping_to_string(description,
                          command_results)

    if shell_results.returncode == successful_return_code:
        print(printable_shell_results)
    else:
        raise Exception(f'\n{printable_shell_results:s}')


def interpret_language_standard(human_readable_language_standard: str) -> tuple[str, str, list[str]]:

    two_digit_year: int
    language_standard: str
    compiler_cli_name: str
    source_file_extensions: list[str]

    matched_C_Plus_Plus_standard: re.Match[str] | None = \
        re.fullmatch(r'C\++ 20(\d\d)',
                     human_readable_language_standard)

    matched_C_standard: re.Match[str] | None = \
        re.fullmatch(r'C (19|20)(\d\d)',
                     human_readable_language_standard)

    if matched_C_Plus_Plus_standard:
        two_digit_year = int(matched_C_Plus_Plus_standard.groups()[0])

        if two_digit_year - 11 > 0:
            if (two_digit_year - 11) % 3 == 0:

                C_PLUS_PLUS_LANGUAGE_STANDARDS: list[str] = ['++0x', '++1y', '++1z', '++2a', '++2b']

                compiler_cli_name = 'g++'
                language_standard = C_PLUS_PLUS_LANGUAGE_STANDARDS[int((two_digit_year - 11)/3)]
                source_file_extensions = ['.cc', '.cxx', '.cpp']

    elif matched_C_standard:

        century: int = int(matched_C_standard.groups()[0])
        two_digit_year = int(matched_C_standard.groups()[1])

        if 100*century + two_digit_year in [1989, 1990, 1999, 2011, 2018]:

            compiler_cli_name = 'gcc'
            language_standard = f'{two_digit_year:d}'
            source_file_extensions = ['.c']

    else:
        raise Exception(f'\'{human_readable_language_standard:s}\' is not a recognized C\\C++ Language Standard')

    return (compiler_cli_name,
            language_standard,
            source_file_extensions)


def interpret_build_configuration(build_configuration: str) -> list[str]:

    build_config_flags: list[str]

    match build_configuration:
        case 'Debug':
            build_config_flags = ['ggdb']
        case 'Release':
            build_config_flags = ['O2', 'DNDEBUG']
        case _:
            raise Exception('\'{build_configuration:s}\' is not a recognized build configuration')

    return build_config_flags


def compile_object_file(compiler_cli_name: str,
                        source_file_path: Path,
                        object_file_path: Path,
                        language_standard: str,
                        build_configuration: str = 'Debug',
                        include_directories: list[Path] | None = None,
                        preprocessor_macros: list[str] | None = None,
                        warnings: list[str] | None = None,
                        treat_warnings_as_errors: bool = False,
                        disable_compiler_extensions: bool = False) -> None:

    if warnings:

        FLAG_PER_WARNING: dict[str, str] = \
            {'Avoid a lot of questionable coding practices': 'all',
             'Avoid even more questionable coding practices': 'extra',
             'Follow Effective C++ Style Guidelines': 'effc++',
             'Avoid potentially value-changing implicit conversions': 'conversion',
             'Avoid potentially sign-changing implicit conversions for integers': 'sign-conversion'}

        for warning in warnings:
            if warning not in FLAG_PER_WARNING:
                raise Exception(f'\'{warning:s}\' is not a recognized warning flag.')

        if '++' not in language_standard and 'Follow Effective C++ Style Guidelines' in warnings:
            raise Exception('Cannot specify Effective C++ Style Guidelines for a C code base')

        warning_flags = [FLAG_PER_WARNING[warning] for warning in warnings]

        if treat_warnings_as_errors:
            warning_flags.append('error')

    compile_command: str = '{compiler:s} -c {source_file:s} -o {object_file:s} {language_standard:s} {build_configuration:s} {miscellaneous:s} {header_locations:s} {warnings:s} {preprocessor_macros:s}'  # noqa: E501

    common_path: Path = \
        Path(commonpath([source_file_path,
                         object_file_path]))

    run_shell_command(f'Compile \'{source_file_path.name:s}\'',
                      compile_command.format(compiler=compiler_cli_name,
                                             source_file=str(source_file_path.relative_to(common_path)),
                                             object_file=str(object_file_path.relative_to(common_path)),
                                             language_standard=f'-std=c{language_standard:s}',
                                             build_configuration=' '.join([f'-{flag:s}' for flag in interpret_build_configuration(build_configuration)]),                                # noqa: E501
                                             miscellaneous='-pedantic-errors' if disable_compiler_extensions else '',
                                             header_locations=' '.join([f'-I {str(include_directory):s}' for include_directory in include_directories]) if include_directories else '',  # noqa: E501
                                             warnings=' '.join([f'-W{warning_flag:s}' for warning_flag in warning_flags]) if warnings else '',                                           # noqa: E501
                                             preprocessor_macros=' '.join([f'-D{macro:s}' for macro in preprocessor_macros]) if preprocessor_macros else '').rstrip(),                   # noqa: E501
                      common_path)


def link_object_files_into_executable(linker_cli_name: str,
                                      executable_path: Path,
                                      object_file_paths: list[Path],
                                      library_directories: list[Path] | None = None,
                                      library_names: list[str] | None = None) -> None:

    link_command: str = '{linker:s} -o {executable:s} {object_files:s} {library_locations:s} {libraries:s}'

    common_path: Path = Path(commonpath([executable_path] + object_file_paths))

    run_shell_command(f'Link into \'{executable_path.stem:s}\' Executable',
                      link_command.format(linker=linker_cli_name,
                                          executable=str(executable_path.relative_to(common_path)),
                                          object_files=' '.join([str(object_file_path.relative_to(common_path)) for object_file_path in object_file_paths]),                          # noqa: E501
                                          library_locations=' '.join([f'-L {str(library_directory):s}' for library_directory in library_directories]) if library_directories else '',  # noqa: E501
                                          libraries=' '.join([f'-l{library_name:s}' for library_name in library_names]) if library_names else '').rstrip(),                            # noqa: E501
                      common_path)


def test_executable(executable_path: Path) -> None:

    run_shell_command(f'Run \'{executable_path.stem:s}\' Executable',
                      f'./{executable_path.name}',
                      executable_path.parent)


def main() -> None:

    #============================================================================================================# noqa: E265, E501
    #============================================================================================================# noqa: E265, E501
    repository_path: Path = Path.cwd()
    executable_name: str = '01_hello_SDL'
    language_standard: str = 'C++ 2023'
    dependency_names: list[str] = ['SDL2', 'SDL2_image', 'fmt']
    #============================================================================================================# noqa: E265, E501
    #============================================================================================================# noqa: E265, E501

    source_directory: Path = repository_path/'src'

    build_directory: Path = repository_path/'build'
    if not build_directory.exists():
        build_directory.mkdir()

    object_directory: Path = build_directory/'obj'
    if not object_directory.exists():
        object_directory.mkdir()

    binary_directory: Path = build_directory/'bin'
    if not binary_directory.exists():
        binary_directory.mkdir()

    try:

        current_source_path: Path
        current_object_path: Path
        object_paths: list[Path] = []
        executable_path: Path = binary_directory/f'{executable_name:s}.exe'

        (compiler_cli_name,
         language_standard,
         source_file_extensions) = \
            interpret_language_standard(language_standard)

        warnings: list[str] = \
            ['Avoid a lot of questionable coding practices',
             'Avoid even more questionable coding practices',
             'Follow Effective C++ Style Guidelines',
             'Avoid potentially value-changing implicit conversions',
             'Avoid potentially sign-changing implicit conversions for integers']

        reduced_warnings: list[str] = \
            ['Follow Effective C++ Style Guidelines',
             'Avoid potentially value-changing implicit conversions',
             'Avoid potentially sign-changing implicit conversions for integers']

        for root, _, files in source_directory.walk():
            for file in files:

                current_source_path = root/file
                current_object_path = object_directory/root.relative_to(source_directory)/f'{current_source_path.stem:s}.o'  # noqa: E501

                if not current_object_path.parent.exists():
                    current_object_path.parent.mkdir()

                if current_source_path.suffix in source_file_extensions:

                    try:
                        compile_object_file(compiler_cli_name,
                                            current_source_path,
                                            current_object_path,
                                            language_standard,
                                            warnings=reduced_warnings if current_source_path.stem == '01_hello_SDL' else warnings,  # noqa: E501
                                            treat_warnings_as_errors=True,
                                            disable_compiler_extensions=True)

                    except Exception as error:
                        raise error

                    else:
                        object_paths.append(current_object_path)

        link_object_files_into_executable(compiler_cli_name,
                                          executable_path,
                                          object_paths,
                                          library_names=dependency_names)

    except Exception:
        print(traceback.format_exc())

    else:
        test_executable(executable_path)

        if build_directory.exists():
            shutil.rmtree(build_directory)


if (__name__ == '__main__'):

    main()
