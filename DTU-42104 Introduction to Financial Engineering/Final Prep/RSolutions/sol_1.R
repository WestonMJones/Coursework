# Install the quantmod package if not downloaded
#install.packages("quantmod")

# Load the quantmod package
library(quantmod)

# Fetch weekly XOM historical prices
getSymbols('XOM', from = "1995-02-20", to = "2019-09-03", periodicity = 'weekly', return.class="data.frame")

# Plot the weekly closing and adjusted closing prices on the same graph
dates = as.Date(rownames(XOM))
plot(dates, XOM$XOM.Close, type = 'l', xlab = 'Time',ylab = 'Price', main = 'Plot of XOM historical closing and adj. closing prices')
lines(dates,XOM$XOM.Adjusted, col = 'red')
legend("topleft", legend = c('Closing Price','Adj. Closing Price'), col = c('black','red'), lty = c(1,1))


# Define a function that calculate returns

CalcReturns = function(prices){
  return( diff(prices) / prices[-length(prices)])
}

# Compute weekly returns with function


WeeklyReturns = CalcReturns(XOM$XOM.Adjusted)


# Compute average weekly returns with geometric mean

geoMean = function(returns){
  n = length(returns)
  return(prod(1 + returns, na.rm = TRUE)^(1/n) - 1)
}

AvgWeeklyReturns = geoMean(WeeklyReturns)
AvgWeeklyReturns


# Compute the std of the returns

sd(WeeklyReturns, na.rm = TRUE)


# Compute the log returns

Adj_Prices = XOM$XOM.Adjusted
WeeklyLogReturns = log(Adj_Prices[-1]) - log(Adj_Prices[1:length(Adj_Prices)-1])

# Compute the average weekly log returns
AverageLogReturns = mean(WeeklyLogReturns)
AverageLogReturns

# Plot the log returns and compare the difference between the "real" 

plot(dates[-1],WeeklyLogReturns, type ='l', col = 'blue', lwd = 3.6, xlab = 'Time',ylab = 'Return')
lines(dates[-1],as.vector(WeeklyReturns)-WeeklyLogReturns, lwd = 1.2)
legend('bottomleft',legend = c('Log Returns','Log Returns - Returns') ,col = c('blue','black'), lty = c(1,1), lwd = c(2,2))


#### PART 3 ####

tickers = c('SPY','XLF','EEM')
from_date = '2005-01-01'
to_date = '2019-09-03'

# Fetch data 
getSymbols(tickers, from = from_date, to = to_date, periodicity = 'daily', src = 'yahoo', return.class="data.frame")



# Store the dates
dates = as.Date(rownames(SPY))

# Plot the adj. closing prices 

plot(dates,SPY$SPY.Adjusted, type = 'l', lwd = 2, xlab = 'Time', ylab = 'Price', ylim = c(0,300) ,main = 'Plot of Adj. closing prices for "SPY","EEM" and "XLF"')
lines(dates, XLF$XLF.Adjusted, col = 'red', lwd = 2)
lines(dates, EEM$EEM.Adjusted, col = 'blue', lwd = 2)
legend('topleft', legend = c('SPY','XLF','EEM'), lty = c(1,1,1), lwd = c(2,2,2), col = c('black','red','blue'))

# Notice that you cant really see the evolution of XLF and EEM due to the magnitude of
# the SPY security. It could make more sense to plot XLF and EEM in a plot for themselves then

# Compute the daily returns of each security

SPY_Returns = CalcReturns(SPY$SPY.Adjusted)
XLF_Returns = CalcReturns(XLF$XLF.Adjusted)
EEM_Returns = CalcReturns(EEM$EEM.Adjusted)

# Compute the average daily returns

SPY_Avg = geoMean(SPY_Returns)
SPY_Avg

XLF_Avg = geoMean(XLF_Returns)
XLF_Avg

EEM_Avg = geoMean(EEM_Returns)
EEM_Avg

# Compute the standard deviation 

sd(SPY_Returns, na.rm = TRUE)
sd(XLF_Returns, na.rm = TRUE)
sd(EEM_Returns, na.rm = TRUE)

# Compute the correlation and covariance matrix

cov(cbind(SPY_Returns[-1],XLF_Returns[-1], EEM_Returns[-1]))
cor(cbind(SPY_Returns[-1],XLF_Returns[-1], EEM_Returns[-1]))

