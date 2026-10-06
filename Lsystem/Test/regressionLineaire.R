# Estimates a fractal dimension by linear regression on the box-counting data.
#
# The relation N ~ c * s^d becomes log(N) ~ log(c) + d * log(s) once logged, so
# the slope of log(N) against log(s) is the dimension d. The .txt files hold
# those logs already, one sample per line, written by the C++ programs:
#   - dataXFlocon.txt / dataYFlocon.txt from Fractales/FloconDeKoch.cpp
#   - dataXRameau.txt / dataYRameau.txt from Lsystem/Test/TestLsystemRameau.cpp
#
# Run from this directory:  Rscript regressionLineaire.R

dimensionFractale <- function(cheminX, cheminY, nom) {
    dataX <- as.numeric(readLines(cheminX))
    dataY <- as.numeric(readLines(cheminY))

    # the first sample is taken at scale 0, whose log is -Inf; the reference
    # scale is 1, so that point is read as log(1) = 0
    dataX[!is.finite(dataX)] <- 0

    regression <- lm(dataY ~ dataX)
    pente <- unname(coef(regression)[2])

    cat(sprintf("%s: dimension = %.4f  (R2 = %.4f, %d points)\n",
                nom, pente, summary(regression)$r.squared, length(dataX)))

    plot(dataX, dataY, xlab = "log(s)", ylab = "log(N)", main = nom, pch = 19)
    abline(regression)

    invisible(regression)
}

dimensionFractale("dataXFlocon.txt", "dataYFlocon.txt", "Koch snowflake")
dimensionFractale("dataXRameau.txt", "dataYRameau.txt", "Branchlet L-system")
