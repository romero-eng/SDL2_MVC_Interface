import numpy as np
import matplotlib.pyplot as plt


def plot_ellipse(a, b, theta_deg, square_lim, x_step, save=True): 

    theta_rad = (np.pi/180)*(theta_deg % 360)
    sin_2_theta = np.sin(2*theta_rad)
    cos_2_theta = np.cos(2*theta_rad)

    norm_sq = ((a*a - b*b)/2)*(1 + cos_2_theta) + b*b

    coeffs = \
        [a*a*sin_2_theta/(2*norm_sq),
         a*b*(1 - cos_2_theta)/(2*norm_sq),
         a*a*b*b*np.square(1 + cos_2_theta)/(4*norm_sq),
         (b*b)*(a*a + b*b)*(np.square((a*a/(a*a + b*b)) + cos_2_theta) - np.square(b*b/(a*a + b*b)))/np.square(2*norm_sq),
         a*b*b*b*sin_2_theta*(1 + cos_2_theta)/np.square(2*norm_sq)]

    upper = 1 if theta_rad < np.pi else -1
    right = 1 if theta_rad <= np.pi/2 or theta_rad >= 3*np.pi/2 else -1
    sgn = lambda x, sign : -np.sign(x - upper*sign*a*np.cos(theta_rad))*upper*right

    y = lambda x, sign: coeffs[0]*x + sign*coeffs[1]*np.sqrt(norm_sq - np.square(x)) + sgn(x, sign)*np.sqrt(coeffs[2] - coeffs[3]*np.square(x) - 2*sign*coeffs[4]*x*np.sqrt(norm_sq - np.square(x)))

    fig, axs = plt.subplots(1)

    x = np.arange(-np.sqrt(norm_sq), np.sqrt(norm_sq), x_step)

    axs.plot(x, y(x,  1))
    axs.plot(x, y(x, -1))

    axs.set_xlim([-square_lim, square_lim])
    axs.set_ylim([-square_lim, square_lim])
    axs.grid()

    fig.supylabel('Y')
    fig.supxlabel('X')

    if(save):
        plt.savefig(f'Y {theta_deg:d}.png')
        plt.close(fig)
    else:
        plt.show()


def plot_ellipse_v2(a, b, theta_deg, square_lim, y_step, save=True):

    theta_rad = (np.pi/180)*(theta_deg % 360)
    sin_2_theta = np.sin(2*theta_rad)
    cos_2_theta = np.cos(2*theta_rad)

    norm_sq = (b*b - a*a)*np.square(np.cos(theta_rad)) + np.square(a)

    coeffs = \
        [b*b*sin_2_theta/(2*norm_sq),
         a*b*(1 - cos_2_theta)/(2*norm_sq),
         a*a*b*b*np.square(1 + cos_2_theta)/(4*norm_sq),
         a*a*(a*a + b*b)*(np.square((b*b/(a*a + b*b)) + cos_2_theta) - np.square(a*a/(a*a + b*b)))/np.square(2*norm_sq),
         a*a*a*b*sin_2_theta*(1 + cos_2_theta)/np.square(2*norm_sq)]

    lower = 1 if theta_rad > np.pi else -1
    right = 1 if theta_rad <= np.pi/2 or theta_rad >= 3*np.pi/2 else -1
    sgn = lambda y, sign : -np.sign(y - lower*sign*b*np.cos(theta_rad))*lower*right

    x = lambda y, sign: -coeffs[0]*y + sign*coeffs[1]*np.sqrt(norm_sq - np.square(y)) + sgn(y, sign)*np.sqrt(coeffs[2] - coeffs[3]*np.square(y) + 2*sign*coeffs[4]*y*np.sqrt(norm_sq - np.square(y)))

    fig, axs = plt.subplots(1)

    y =  np.arange(-np.sqrt(norm_sq), np.sqrt(norm_sq), y_step)

    axs.plot(x(y,  1), y)
    axs.plot(x(y, -1), y)

    axs.set_xlim([-square_lim, square_lim])
    axs.set_ylim([-square_lim, square_lim])
    axs.grid()

    fig.supylabel('Y')
    fig.supxlabel('X')

    if(save):
        plt.savefig(f'X {theta_deg:d}.png')
        plt.close(fig)
    else:
        plt.show()


if (__name__ == "__main__"):

    a: int | float = 2
    b: int | float = 5
    square_lim: int = 7
    step: float = 0.001

    for theta_deg in np.arange(0, 370, 10):
        plot_ellipse(   a, b, theta_deg, square_lim, step)
        plot_ellipse_v2(a, b, theta_deg, square_lim, step)
