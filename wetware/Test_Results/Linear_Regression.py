#!/usr/bin/env python
##
## Python Script for performing linear regression
## on Stock Cortisol Characterization Results
## This script takes optical density results and performs a linear
## regression on a logarithmic scale

## Requires Scipy and numpy

import numpy as np
from scipy import special, optimize
from scipy import stats

## Data
optical_density = np.array([.062,.112,.194,.314,.4,.504,.606,])
concentration = np.array([10,5,2.5,1.25,.625,.313,.156,])
log_concentration = np.log10(concentration)

## Linear Regression
slope, intercept, r_value, p_value, std_err = stats.linregress(log_concentration, optical_density)

# print slope, intercept, and r_value
if __name__ == '__main__':
    print("Slope:\t\t{}".format(slope))
    print("Intercept:\t{}".format(intercept))
    print("R-value:\t{}".format(r_value))
