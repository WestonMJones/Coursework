#Exercises for Week 2

# Exercise 1(a-b) ----
# Clearing the workspace
rm(list = ls())


# Load the  necessary packages 
library(quantmod)
library(lubridate)
# Load previous weeks data
getSymbols('XOM',src = 'yahoo', from = "1995-02-20",periodicity = "weekly")

# Define it as a data frame for easier access to variables 
XOM = as.data.frame(XOM)

# Save the dates in a seperate variable 
dates = as.Date(rownames(XOM))

# Compute weekly returns and log returns 

# Function to calculate returns
ComputeReturn <- function(x){
  diff(x)/x[-length(x)]
}

WeeklyRet = ComputeReturn(XOM$XOM.Adjusted)


logReturns = log(XOM$XOM.Adjusted[-1]) - log(XOM$XOM.Adjusted[1:length(XOM$XOM.Adjusted)-1])



# Compute the average of the weekly returns and log-returns 

geoMean = function(returns){
  avg = prod(1+returns)^(1/length(returns)) - 1
}

geoAvg = geoMean(WeeklyRet)
geoAvg

AverageLogReturns = mean(logReturns)
AverageLogReturns


# Annualize the weekly returns 
annual_returns = (1+geoAvg)^52 - 1
annual_returns

annual_log_returns = AverageLogReturns*52
annual_log_returns

# 1C: Difference between log annual returns and "normal" returns---- 

annual_returns - annual_log_returns


# Exercise 2a----

# Load data directly with getSymbols, note that this will extract updated data from the day you issue the command
#unless you type in a "to" input


getSymbols(c('SPY','XLF','EEM'), src = 'yahoo', from = '2004-12-31',to='2018-09-01')

# Store in data frames 
SPY = as.data.frame(SPY)
XLF = as.data.frame(XLF)
EEM = as.data.frame(EEM)
# To analyse big data you can make a quick sanity check by looking at the first and last rows with the following
# ?head
# ?tail
head(SPY)
tail(SPY)

# Store the new dates in a variable 
dates2 = as.Date(rownames(SPY))

# Compute returns for each ETF 
SPY_Returns = ComputeReturn(SPY$SPY.Adjusted)
XLF_Returns = ComputeReturn(XLF$XLF.Adjusted)
EEM_Returns = ComputeReturn(EEM$EEM.Adjusted)

# Average the daily returns
AverageReturn_SPY = geoMean(SPY_Returns)
AverageReturn_XLF = geoMean(XLF_Returns)
AverageReturn_EEM = geoMean(EEM_Returns)

# Annualise the daily returns 
SPY_annual = (1+AverageReturn_SPY)^252 - 1
XLF_annual = (1+AverageReturn_XLF)^252 - 1
EEM_annual = (1+AverageReturn_EEM)^252 - 1

# Exercise 2b----
# Annualise the standard deviations 

sd_SPY = sd(SPY_Returns)*sqrt(252)
sd_XLF = sd(XLF_Returns)*sqrt(252)
sd_EEM = sd(EEM_Returns)*sqrt(252)

# Exercise 2c----
# Annualise the covariance matrix 
# Collect all data in a matrix
dailyReturns = cbind(SPY_Returns, XLF_Returns, EEM_Returns)

Var_Cov_Matrix = cov(dailyReturns) * 252

# Compute correlation matrix 
cor_mat = cor(dailyReturns)
cor_mat

# 2.d explanation----
# For the correlation matrix we dont need to do anything since correlation is a normalized quantity 
# and is therefore not affected by the scale of the variables


### Exercise 3 ###


#We start with extracting all the relevant information from the bonds from 
# http://www.nasdaqomxnordic.com/bonds/denmark
#We need the coupon, price and maturity date.

#Getting lubridate
library(lubridate)

#1. Preparing the data----
#Prices extracted on 08.of september
today="2019-09-08"

Bond = c("1,5 St.l 23 GB",
         '3ST.L. 21 GB',
         '4St.l.19 GB',
         'DANSKE STAT 2022',
         'DANSKE STAT 2029',
         'DGBI 2023 GB',
         'DGBi',
         'Danske Stat 2020',
         'Danske Stat 2025',
         'Danske Stat 2027',
         '7 St.l 24 GB',
         '4,5 St.l 39 GB'
)
FaceValue = rep(100, length(Bond))
Price<-c(110.410,108.735,100.830,103.860,112.290,107.420,122.150,101.413,116.840,110.600,141.640,202.240)

Coupon<-c(1.50,3.00,4.00,0.25,0.50,0.10,0.10,0.25,1.75,0.50,7.00,4.50)
Matday<-c("2023-11-15","2021-11-15","2019-11-15","2022-11-15","2029-11-15","2023-11-15","2030-11-15","2020-11-15","2025-11-15","2027-11-15","2024-11-15","2039-11-15")
Matyear<-c(2023,2021,2019,2022,2029,2023,2030,2020,2025,2027,2024,2039)


#Now we combine all the relevant information to a dataframe
bondData <- data.frame(Bond, FaceValue, Coupon, Price, Matday)

#Now we get some more practical information
cashFlowDates <- c(today, seq.Date(from= as.Date("2019-11-15"), to = as.Date("2039-11-15"), by = 'year'))
cashFlowDates

couponsToMaturity <- year(bondData$Matday)-year(today) + 1 ## + 1 because we want to have the coupon payment for 2019 in the cashflows
couponsToMaturity
#We now calculate the dirty price and store it in our dataframe
bondData$dirtyPrice <- bondData$Price + (bondData$Coupon) * as.numeric(difftime(today, "2018-11-15", units = 'days'))/365
bondData

#Part1a Setting up the cashflow for each bond----

# Start by creating an empty CashFlow Matrix which will then be filled
cashFlowsDirty <- matrix(0L, nrow = length(Bond), ncol = length(cashFlowDates))
#Assigning the rowvalues to the bond names
rownames(cashFlowsDirty) <- Bond
#Creating column names as the dates for the cashflows
colnames(cashFlowsDirty) <- as.character(cashFlowDates)
cashFlowsDirty

for (i in 1:length(Bond)){
  cashFlowsDirty[i,1] <- -bondData$dirtyPrice[i]   # Negative Cashflow when bond is bought
  for (j in 1:couponsToMaturity[i]){
    cashFlowsDirty[i,j+1] <- bondData$Coupon[i]   # Coupon payment
    if (j == couponsToMaturity[i]) {
      cashFlowsDirty[i,j+1] <- cashFlowsDirty[i,j+1] + bondData$FaceValue[i]  # Face value of bond paid at Maturity
    }
  }
}
cashFlowsDirty


#Part1b-Calculating the YTM for each bond----

#Function for the uniroot PV of a bond minus the dirty price

bval <- function(yield, Payment, t, dirtyP){
  
  sum(Payment/(1+yield)^t)-dirtyP
  
}

rootsFun<-function(pay,time,dirty){
  
  output<-uniroot(bval,c(-1, 2),Payment=pay, t=time ,dirtyP=dirty)$root #use the interval -2 to 2 meaning the ytm can take values bewteen -100% and 200%
  return(output)
}


YTM_dirty<-c()

for (j in 1:length(Matyear)){
  TimeToPayments<-c()
  Payment<-c()
  
  
  for (i in 2019:Matyear[j]){
    #print(i)
    TimeOfPayments<-seq( as.Date("2019-11-15"), by='year', len=Matyear[j]-2019+1)
    
    TimeToPayments[i-2019+1]<-as.numeric(difftime(TimeOfPayments[i-2019+1], today, units='days'))/365
    
    Payment[i-2019+1]  <- Coupon[j]
  }
  
  Payment[i-2019+1]<-100+Payment[i-2019+1] #adding the last payment to the coupons
  YTM_dirty[j]<-rootsFun(Payment,TimeToPayments,bondData$dirtyPrice[j])
  
  
}

#Part1c-Plotting the bonds' yieldds for each maturity as a function of time to maturity----

#We can now add the YTM to our dataframe if we want
bondData$YTM=YTM_dirty
bondData
#Finally we make the plot and give the axis represantative names
plot(Matyear,bondData$YTM*100,xlab='Time',ylab='Yield to maturity')

#Week39----

  #install.packages('YieldCurve')

  library(YieldCurve)


# Calculating Years to maturities (using the total number of weeks until maturity)
bondData$maturities <- as.numeric(difftime(bondData$Matday, today, unit="weeks"))/52.25
# plot(bondData$maturities, bondData$YTM)

# Following is to get our data in same form as the one seen in example for NSrates and Nelson.Siegel see '?NSrates' (bottom)
bondData1=bondData[order(bondData$maturities),]

yields_raw <- data.frame(as.list(bondData1$YTM))
rownames(yields_raw) <- today
yieldsXts <- as.xts(yields_raw)
yieldsXts

# Compute the Nelson Siegel Parameters

#NSParameters <- Nelson.Siegel(bla, maturity=bondData1$maturities)
NSParameters <- Nelson.Siegel(yieldsXts, maturity=bondData1$maturities)
# Get the fitted Yields for each maturity using the Nelson Siegel parameters
fittedYield <- NSrates(NSParameters, bondData1$maturities)



# Plot the original Yield curve using the original data
plot(bondData1$maturities,yieldsXts[1,],main="Fitting Nelson-Siegel yield curve", type="o",xlab = 'Maturity in Years', ylab = 'Yield',cex.lab = 1.5)
# Add the Nelson.Siegel fitted values
lines(bondData1$maturities, fittedYield, col=2)
legend("bottomright",legend=c("observed yield curve","fitted yield curve"),
       col=c(1,2),lty=1)


#Note that we have to remove one of the bonds, which one? Note that the DGBI bonds are index based bond
#while the others are nominal bonds, so we remove them


bondDataReduced<-bondData[-c(6,7),]

cashFlowsDirtyReduced <- cashFlowsDirty[-c(3,8),]


## Get data ready for Nelson Siegel
bondDataReduced <- bondDataReduced[order(bondDataReduced$maturities),]
yields <- data.frame(as.list(bondDataReduced$YTM))
rownames(yields) <- today

yieldsXts <- as.xts(yields)
yieldsXts

NSParameters <- Nelson.Siegel(yieldsXts, maturity=bondDataReduced$maturities)
fittedYield <- NSrates(NSParameters, bondDataReduced$maturities)

plot(bondDataReduced$maturities,yieldsXts[1,],main="Fitting Nelson-Siegel yield curve", type="o")
lines(bondDataReduced$maturities, fittedYield, col=2)
legend("bottomright",legend=c("observed yield curve","fitted yield curve"),
       col=c(1,2),lty=1)

##### Part2 - Calculation of Duration and Convexity -----


# Function for Calculating Duration
calcDuration <- function(Price, CashFlow, t, r){
  1/Price * sum( t * cf / (1 + r)^(t+1))
}

# Function For Calculating Convexity
calcConvexity <- function(Price, CashFlow, t, r){
  1/Price * sum( t * (t+1) * cf / (1 + r)^(t+2))
}

MACdur <- c() # Empty array to store MAC Duration Calculation
MODdur <- c()
FWdur <- c() # Empty array to store FW Duration Calculation
conv <- c()
FWconv <- c() # Empty array to store Convexity Calculation


for (i in 1:length(bondData$Bond)){
  p <- bondData$dirtyPrice[i]
  cf <- cashFlowsDirty[i, ]
  t <- seq(along = cf)-1
  t[2:length(t)] <- t[2:length(t)] - ( 1 - as.numeric(difftime("2019-11-15", today, units='days'))/365)  # here we account for the time until coupon payment

  r <- as.numeric(NSrates(NSParameters, t)) # Use Nelson Sigel for estimation of rates
  r[1] <- 0                                 # First rate is NaN so we set it to Zero

  MACdur <- c(MACdur, calcDuration(p, cf, t, yields_raw[1,i])*(1+yields_raw[1,i]))
  MODdur <- c(MODdur, calcDuration(p, cf, t, yields_raw[1,i]))
  FWdur <- c(FWdur, calcDuration(p, cf, t, r))
  conv <- c(conv, calcConvexity(p, cf, t, yields_raw[1,i]))
  FWconv <- c(FWconv, calcConvexity(p, cf, t, r))
}

bondData$MACDuration <- MACdur 
bondData$MODDuration <- MODdur
bondData$FWDuration <- FWdur
bondData$Convexity <- conv
bondData$FWConvexity <- FWconv

bondData


