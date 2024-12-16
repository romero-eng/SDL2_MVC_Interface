import numpy as np
import matplotlib.pyplot as plt


def plot_ellipse(a, b, theta_deg, square_lim, x_step, save=True): 

    theta_rad = (np.pi/180)*(theta_deg % 360)
    sin_theta_rad = np.sin(theta_rad)
    cos_theta_rad = np.cos(theta_rad)

    A = a*cos_theta_rad
    B = b*sin_theta_rad
    norm_sq = np.square(A) + np.square(B)
    norm = np.sqrt(norm_sq)

    nsign = lambda t: 1 - 2*np.heaviside(t, 1)
    x = lambda x_prime, sign: (a/norm_sq)*(A*x_prime + sign*B*np.sqrt(norm_sq - np.square(x_prime)))
    y = lambda x_prime, sign: nsign(x_prime - nsign(theta_rad - np.pi)*sign*A)*nsign(theta_rad - np.pi)*(b/a)*np.sqrt(np.square(a) - np.square(x(x_prime, sign)))
    y_prime = lambda x_prime, sign: x(x_prime, sign)*sin_theta_rad + y(x_prime, sign)*cos_theta_rad

    fig, axs = plt.subplots(1)

    x_prime = np.arange(-norm, norm, x_step)

    axs.plot(x_prime, y_prime(x_prime,  1))
    axs.plot(x_prime, y_prime(x_prime, -1))

    axs.set_xlim([-square_lim, square_lim])
    axs.set_ylim([-square_lim, square_lim])
    axs.grid()
    #axs.axvline( A, color='k')
    #axs.axvline(-A, color='k')

    fig.supylabel('Y')
    fig.supxlabel('X')

    if(save):
        plt.savefig(f'Y {theta_deg:d}.png')
        plt.close(fig)
    else:
        plt.show()


def plot_ellipse_v2(a, b, theta_deg, square_lim, y_step, save=True):

    theta_rad = (np.pi/180)*(theta_deg % 360)

    A = a*np.sin(theta_rad)
    B = b*np.cos(theta_rad)
    norm_sq = np.square(A) + np.square(B)
    norm = np.sqrt(norm_sq)

    nsign = lambda t: 1 - 2*np.heaviside(t, 1)
    y = lambda y_prime, sign : (b/norm_sq)*(B*y_prime - sign*A*np.sqrt(norm_sq - np.square(y_prime)))
    x = lambda y_prime, sign :  -nsign(y_prime + nsign(theta_rad - np.pi)*sign*B)*nsign(theta_rad - np.pi)*(a/b)*np.sqrt(np.square(b) - np.square(y(y_prime, sign)))
    x_prime = lambda y_prime, sign : x(y_prime, sign)*np.cos(theta_rad) - y(y_prime, sign)*np.sin(theta_rad)

    fig, axs = plt.subplots(1)

    y_prime =  np.arange(-norm, norm, y_step)

    axs.plot(x_prime(y_prime,  1), y_prime)
    axs.plot(x_prime(y_prime, -1), y_prime)

    axs.set_xlim([-square_lim, square_lim])
    axs.set_ylim([-square_lim, square_lim])
    axs.grid()
    #axs.axhline( B, color='k')
    #axs.axhline(-B, color='k')

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
