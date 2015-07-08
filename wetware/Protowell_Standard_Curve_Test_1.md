#Protowell System Test

The purpose of this experiment is to see if cortisol can be detected using the protowell system with platinum and silver/silver chloride microelectrodes submerged in treated Nunc microwell plates.

###Materials Needed
1. Thermo Scientific Nunc Immuno Maxisorp 96 well plates (#439454)
5. RnD Cortisol Parameter Assay (PKGE008)
6. Generic Face Mask
6. Abcam Mouse Monoclonal Anti-Cortisol antibody [XM210] (ab1949)(2 mg/mL)
7. RnD Hydrocortisone (4093)
8. Abcam Anti-Cortisol antibody (ab157451)(0.094mg/mL)
9. Abcam Alkaline phosphatase Conjugation Kit (ab102850)
10. 4-Aminophenyl phosphate monosodium salt (ab141899)
11. Platinum electrodes
12. Silver/Silver Chloride Electrodes
13. CheapStat
14. Driver
15. Gui


###Methods

####Elisa Assay

######Assay Procedure

1. Bring all reagents to room temperature before use.
2. Cortisol is found in saliva. It is recommended that a face mask and gloves be used to protect kit reagents from contamination.
1. Remove excess microplate strips from the plate frame, return them to the foil pouch containing the desiccant pack, and reseal.
2. Add 150 μL of Calibrator Diluent RD5-43 into the non-specific binding (**NSB**) wells.
3. Add 100 μL of Calibrator Diluent RD5-43 to the zero standard (**B0**) wells.
4. Cortisol Standard
	1. Reconstitute the Cortisol Standard with deionized or distilled water. This reconstitution produces a stock solution of 100 ng/mL. Mix the standard to ensure complete reconstitution and allow the standard to sit for a minimum of 15 minutes with gentle agitation prior to making dilutions.
	3. Use the 100 ng/mL standard stock to produce a dilution series.
	4. Mix each tube thoroughly and change pipette tips between eachtransfer. The 10 ng/mL standard serves as the high standard and Calibrator Diluent RD5-43 serves as the zero standard (B0)(0 ng/mL).
	5. Use diluted standards within 60 minutes of preparation
7. Sample Prep
	1. Reconstitute hydrocortison in 3mL of DI water
	2. Perform Dilutions to create concentrations in Test Setup
4. Add 100 μL of Standard or sample to the appropriate wells(**See Test Setup**)
5. Add 50 μL of Cortisol Conjugate to all wells. Wells will now be red in color.
6. Add 50 μL of the Primary Antibody Solution to each well (**excluding the NSB wells**).
7. Cover with the adhesive strip provided. All wells will now be violet in color except the NSB wells, which will be red in color.
8. Incubate for 2 hours at room temperature on a horizontal orbital microplate shaker (**0.12" orbit**) set at 500 ± 50 rpm.
9. Substrate Solution : Color Reagents A and B should be mixed together in equal volumes within 15 minutes of use. Protect from light. 200 μL of the resultant mixture is required per well.
9. Wash Buffer : If crystals have formed in the concentrate, warm to room temperature and mix gently until the crystals have completely dissolved. Add 20 mL of Wash Buffer Concentrate to deionized or distilled water to prepare 500 mL of Wash Buffer.
9. Aspirate each well and wash, repeating the process three times for a total of four washes. Wash by filling each well with Wash Buffer (**400 μL**) using a squirt bottle, manifold dispenser, or autowasher. Complete removal of liquid at each step is essential for good performance. After the last wash, remove any remaining Wash Buffer by aspirating or decanting. Invert the plate and blot it against clean paper towels.
11. Add 200 μL of Substrate Solution to each well. Incubate for 30 minutes at room temperature on the benchtop. Protect from light.
12. Add 50 μL of Stop Solution to each well. The color in the wells should change from blue to yellow. If the color in the well is green or the color change does not appear uniform, gently tap the plate to ensure thorough mixing.
13. Determine the optical density of each well within 30 minutes, using a microplate reader set to 450 nm. If wavelength correction is available, set to 540 nm or 570 nm. If wavelength correction is not available, subtract readings at 540 nm or 570 nm from the readings at 450 nm. This subtraction will correct for optical imperfections in the plate. Readings made directly at 450 nm without correction may be higher and less accurate.

####Protowell System Assay

####Day 1

######Solution Preperation
1. Mouse Monoclonal Antibody : Dilute

######Preparation of Nunc Immuno Wells

1. Pipette 350 microliters of mouse monoclonal antibody solution(10 mg/L) in all wells except blank.
2. Incubate at 4C overnight.

######Preperation of ALP Conjugated Polyclonal Antibody
1. Spin down Polyclonal antibody for a short period of time.
1. Before you add antibody to the AP mix, add 10µl of Modifier reagent to the antibody sample for each 100µl of antibody to be labeled. Mix gently.
2. Pipette the antibody sample (**with added Modifier**) directly onto the lyophilised material. Resuspend gently by withdrawing and re-dispensing the liquid once or twice using a pipette.
3. Place the cap back on the vial and leave the vial standing for 3 hours at room temperature (20-25°C). Alternatively, and sometimes more conveniently, conjugations can be set up and left overnight, as the longer incubation time has no negative effect on the conjugate.


####Day 2

######ALP Conjugated Antibodies
1. After incubating for 3 hours (or more), add 1µl of Quencher reagent for every 10µl of antibody used. The conjugate can be used after 30 minutes.

######Nunc Immuno Wells
1. Wash wells with PBS.
2. Pipette 350 microliters of BSA solution (5% in 10mM PBS) into all wells except Blank
3. Let sit for 3 hours
4. Pipette Hydrocortisone at concentrations shown in Test Setup(**Refer Below**)
5. Pipette 100 microliters of Conjugated Antibody Solution (10mg/L) to all wells except blank
6. Analyze using plate reader at 400nm
7. Add 100 microliters of PAPP (500 microgram/mL) to all wells except blank
8. Place Electrodes in each well and perform a Cyclic Voltammogram from -0.3V to +0.3V at 50mV/S
9. Record data

###Test Setup

| Elisa Plate Col 1 | Elisa PLate Col 2 |
| ----------------- | ----------------- |
|10 ng/mL|10 ng/mL|
|5 ng/mL|10 ng/mL|
|2.5 ng/mL|0.625 ng/mL|
|1.25 ng/mL|0.625 ng/mL|
|0.625 ng/mL|0.156 ng/mL|
|0.313 ng/mL|0.156 ng/mL|
|0.156 ng/mL|NSB|
| Zero |NSB|

| Nunc Immuno Plate Col 1 | Nunc Immuno Plate Col 2 |
|------------------------ | ----------------------- |
|1.5 mg/mL|1.5mg/mL|
|0.3 mg/mL|0.3mg/mL|
|0.06 mg/mL|0.06 mg/mL|
|12000 ng/mL|12000 ng/mL|
|2400 ng/mL|2400 ng/mL|
|480 ng/mL|480ng/mL|
|96 ng/mL|96 ng/mL|
|19.2 ng/mL|19.2ng/mL|
|3.84 ng/mL|3.84 ng/mL|
|0.768 ng/mL|0.768 ng/mL|
|0.1536 ng/mL|0.1536 ng/mL|
|Blank|Blank|

