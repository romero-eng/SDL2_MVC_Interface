import numpy as np
import matplotlib.pyplot as plt

if(__name__=="__main__"):

    P_0 = np.array([ 0, 0])
    P_1 = np.array([ -2, 4])
    P_2 = np.array([10, 0])
    t_step = 0.001

    x_0 = P_0[0]
    x_1 = P_1[0]
    x_2 = P_2[0]
    y_0 = P_0[1]
    y_1 = P_1[1]
    y_2 = P_2[1]

    t = np.arange(0, 1 + t_step, t_step)
    x_t = (1 - t)*((1 - t)*x_0 + t*x_1) + t*((1 - t)*x_1 + t*x_2)
    y_t = (1 - t)*((1 - t)*y_0 + t*y_1) + t*((1 - t)*y_1 + t*y_2)

    fig, axs = plt.subplots(1)
    axs.plot(x_t, y_t, 'r')
    axs.plot(x_0, y_0, 'kx')
    axs.plot(x_1, y_1, 'kx')
    axs.plot(x_2, y_2, 'kx')
    axs.plot([x_0, x_1], [y_0, y_1], 'b')
    axs.plot([x_1, x_2], [y_1, y_2], 'b')

    axs.set_xlim([min(x_0, x_1, x_2) - 1, max(x_0, x_1, x_2) + 1])
    axs.set_ylim([min(y_0, y_1, y_2) - 1, max(y_0, y_1, y_2) + 1])
    axs.grid()

    fig.supylabel('Y')
    fig.supxlabel('X')

    plt.savefig(f'Quadratic Bezier.png')
    plt.close(fig)
