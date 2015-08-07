# Results for Stock Cortisol Characterization Test

## Document Info

 - Data is measured in terms of **Optical Density** (O.D. Wavelength~nm).
 - Calculations to get the main result are **Corrected Optical Density** (Result - Correction - NSB), **Average Corrected Optical Desnity** (Duplicates Averaged), and **Logarithmic Regression**
 - The main reuslts are **Calculated Sample Concentration** and **Percent Error**.

## Test Setup

| Standard Concentration | Hypothesized Sample Concentration |
| ---------------------- | --------------------------------- |
| 10 ng/mL               | 10 ng/mL                          |
| 5 ng/mL                | 10 ng/mL                          |
| 2.5 ng/mL              | 0.625 ng/mL                       |
| 1.25 ng/mL             | 0.625 ng/mL                       |
| 0.625 ng/mL            | 0.156 ng/mL                       |
| 0.313 ng/mL            | 0.156 ng/mL                       |
| 0.156 ng/mL            | NSB                               |
| Zero                   | NSB                               |

## Optical Density (Collected Data)

| Standard Result (O.D. 450nm) | Sample Result (O.D. 450nm) |
| ---------------------------- | -------------------------- |
| 0.113                        | 0.096                      |
| .163                         | 0.083                      |
| 0.243                        | 0.39                       |
| 0.365                        | 0.415                      |
| 0.457                        | 0.572                      |
| 0.557                        | 0.605                      |
| 0.671                        | 0.046                      |
| 0.739                        | 0.045                      |

|Standard Correction (O.D. 570nm) | Sample Correction( O.D. 570nm) |
| ------------------------------- | ------------------------------ |
| 0.049                           | 0.047                          |
| 0.05                            | 0.043                          |
| 0.049                           | 0.049                          |
| 0.051                           | 0.048                          |
| 0.057                           | 0.048                          |
| 0.053                           | 0.052                          |
| 0.065                           | 0.044                          |
| 0.06                            | 0.044                          |

### Corrected Optical Density

|Standard Corrected (O.D. 570nm) | Sample Corrected (O.D. 570nm) |
| ------------------------------ | ----------------------------- |
| 0.062                          | 0.0475                        |
| 0.112                          | 0.04                          |
| 0.194                          | 0.341                         |
| 0.314                          | 0.367                         |
| 0.4                            | 0.524                         |
| 0.504                          | 0.553                         |
| 0.606                          | 0.002                         |
| 0.679                          | 0.001                         |

### Average and Reformatted Corrected Data
#### Setup

| Standard Concentration | Sample Concentration |
| ---------------------- | -------------------- |
| 10 ng/mL               | 10 ng/mL             |
| 5 ng/mL                | 0.625 ng/mL          |
| 2.5 ng/mL              | 0.156 ng/mL          |
| 1.25 ng/mL             |                      |
| 0.625 ng/mL            |                      |
| 0.313 ng/mL            |                      |
| 0.156 ng/mL            |                      |
| Zero                   |                      |

#### Data

| Corrected Standard O.D. | Corrected Average Sample O.D. |
| ----------------------- | ----------------------------- |
| 0.062                   | 0.04375                       |
| 0.112                   | 0.354                         |
| 0.194                   | 0.5385                        |
| 0.314                   |                               |
| 0.4                     |                               |
| 0.504                   |                               |
| 0.606                   |                               |
| 0.679                   |                               |

## Logarithmic Regression

A logarithmic regression was performed using a python script called [Logarithmic_Regression.py](./Logarithmic_Regression.py) where:

    x values = Log_base_10(Standard Concentration) = Log[10ng/ml 5ng/mL 2.5ng/mL 1.25ng/mL 1.25ng/mL 0.625ng/mL 0.313ng/mL 0.156ng/mL]
    y values = Corrected Standard Optical Density = [0.062 0.112 0.194 0.314 0.4 0.504 0.606 0.679]

The result equation of the line is **Y = -0.135ln(x) + 0.3435** with an **R Squared Value of 0.9922**.

## Calculated Sample Concentration

The Corrected Average Sample O.D. values [0.04375 354 5385] were plugged in to the Logarithmic regression Equation shown above using a python script called [Sample_Concetration_Calculation.py](./Sample_Concentration_Calculation.py)

| Calculated Sample Concentration (ng/mL) |
| --------------------------------------- |
| 9.2107                                  |
| 0.9252                                  |
| 0.2359                                  |

## Error

Absolute Error and Precent Error were calculated by [Error.py](./Error.py)

    Absolute Error = |(Calculated Sample Concentration - Hypythesized Sample Concentration)|

|Absolute Error|
|--------------|
|0.9230|
|0.3020|
|0.0827|

    Percent Error = |(Calculated Sample Concentration - Hypythesized Sample Concentration)| / Calculated Sample Concentration * 100

|Percent Error|
|--------------|
|0.1017|
|0.3258|
|0.3464|

## Conclusion

The concentration of Stock Cortisol Solution is approximately **50 mg/mL**, and the error should be **plus or minus 1 ng/mL**.


