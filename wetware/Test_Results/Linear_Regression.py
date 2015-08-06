#!/usr/bin/env python
#
# Python Script for performing logistic regression
# on Stock Cortisol Characterization Results
#
# Requires Scipy and numpy


import argparse
import numpy as np
from scipy import special, optimize, stats
import matplotlib.pyplot as plt


## Data
optical_densities = np.array([0.062, 0.112, 0.194, 0.314, 0.4, 0.504, 0.606])
concentrations = np.array([10.0, 5.0, 2.5, 1.25, 0.625, 0.313, 0.156])
log_concentrations = np.log10(concentrations)


## Linear Regression
slope, intercept, r_value, p_value, std_err = stats.linregress(log_concentrations, optical_densities)


def plot_results():
    plt.figure()
    # First add original data
    plt.plot(optical_densities, concentrations, 'ro', label="Original Data")
    plt.plot(log_concentrations, 'ko', label="log of concentrations")
    plt.legend()
    plt.show()


def print_results(slope, intercept, r_value):
    print("Slope:\t\t{}".format(slope))
    print("Intercept:\t{}".format(intercept))
    print("R-value:\t{}".format(r_value))


# print slope, intercept, and r_value
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Calculate and optionally plot the regression results.")
    parser.add_argument('-p', '--plot', help="Toggle the plot (matplotlib)", action='store_true')
    args = parser.parse_args()

    print_results(slope, intercept, r_value)
    plot_results() if args.plot == True else None
