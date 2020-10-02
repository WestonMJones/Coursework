#### Exercise 1 ####

library(quantmod)

# Define the tickers and get the data
tickers = c('MCD','KO','MSFT')
getSymbols(Symbols = tickers , from = '1994-1-1', to = '2001-1-1', periodicity = 'weekly', return.class = 'data.frame')

# Store the dates
dates = rownames(MCD)


## Compute the portfolio weights for the GMV and Tangent portfolio -- Assume risk free rate is 2% ##

## Compute weekly returns first and store into a data frame ##
returnCalc <- function(x){
  diff(x)/x[-length(x)]
}

Returns = setNames(data.frame(matrix(ncol = length(tickers), nrow = length(dates)-1), row.names = dates[-1]), tickers)

Returns$MCD = returnCalc(MCD$MCD.Adjusted)
Returns$KO = returnCalc(KO$KO.Adjusted)
Returns$MSFT = returnCalc(MSFT$MSFT.Adjusted)

## Compute and annualise the expected return. Find the covariance matrix as well ##

geomAveCalc <- function(x){
  (prod((1+x)))^(1/length(x))-1
}

WeeklyAvg = apply(Returns, 2, geomAveCalc)
YearlyAvg = ((1+WeeklyAvg)^52) - 1  

covMat = cov(Returns) * 52  ## Annualised covariance matrix ##


## Define the A matrix from the calculation of the efficient frontier ##
l_mat = matrix(YearlyAvg,c(1,1,1), nrow = 2, ncol = 3)
l_mat[2,] = 1
r_mat = matrix(YearlyAvg, nrow = 3, ncol = 2)
r_mat[,2] = 1

A = l_mat %*% solve(covMat) %*% r_mat

a = A[1,1]
b = A[1,2]
c = A[2,2]

# Plot the efficient frontier

mu_P = seq(0.05, 0.4, 0.01)
sigma_P = seq(0,0.4,0.01)
plot( sqrt((c*mu_P^2 - 2*b*mu_P + a) / (a*c-b^2)), type = 'l', lwd = 2, mu_P, xlab = 'Risk',ylab = 'Expected return', ylim = c(0,0.4),xlim = c(0,0.5),main = 'CML and Efficient Frontier' ) 
points((sqrt(1/c)), b/c, pch = 'x', col = 'red', cex = 1.5)  

# Compute the GMV portfolio #
w_gmv = (1/c) * solve(covMat) %*% matrix(1,nrow = 3, ncol = 1)  # Find the portfolio weights of the GMV portoflio 
mu_gmv = t(YearlyAvg) %*% w_gmv 
sigma_gmv = t(w_gmv) %*% covMat %*% w_gmv

# Compute the CML (risk free rate is 2%) #

rf = 0.02
mu_e = YearlyAvg - rf 
#lines((mu_P-rf)/sqrt(t(YearlyAvg) %*% solve(covMat) %*% YearlyAvg), mu_P-rf, lwd = 2, col = 'blue')
lines(sigma_P, sigma_P*sqrt(t(mu_e)%*% solve(covMat)%*%mu_e) + rf, lwd = 2, col='blue')

# Compute tangent portfolio and plot it #

mu_tan = (t(mu_e) %*% solve(covMat) %*% mu_e) / (matrix(1,nrow=1, ncol= 3) %*% solve(covMat) %*% mu_e) 
sigma_tan = sqrt((t(mu_e) %*% solve(covMat) %*% mu_e)) / (matrix(1,nrow=1, ncol= 3) %*% solve(covMat) %*% mu_e)
points(sigma_tan, mu_tan+rf, pch = 'x', cex = 1.5, col = 'magenta')

# Find the weights of the tangent portfolio #

w_tan = (solve(covMat) %*% mu_e) %*% (mu_tan / (t(mu_e) %*% solve(covMat) %*% mu_e))


# Pick a point mu_C between the GMV and Tangent portfolio and find the portfolio. In this case we set mu_C = 0.25 or 25% #

mu_C = 0.25
w_C = solve(covMat) %*% r_mat %*% solve(A) %*% matrix(c(0.25,1),nrow=2,ncol=1)

C_portfolio_avg = t(YearlyAvg) %*% w_C
C_portfolio_risk = sqrt(t(w_C) %*% covMat %*% w_C)


## Find a fraction alpha that fulfills the described criterias ##

alpha = 1 - (mu_C - mu_gmv) / ((mu_tan+rf) - mu_gmv)

w_tmp = as.numeric(alpha) * as.matrix(w_gmv) + as.numeric((1-alpha)) * as.matrix(w_tan)

## Check if the 2 portfolios are identical ##
w_tmp - w_C

## Confirm that for each asset, the ratio of excess return to its' covariance with the tangent
## portfolio is identical. Hint: The covariance of asset with the tangent portfolio is easily
## obtained by multiplying portfolio weights with the covariance matrix.


mu_e / (t(w_tan) %*% covMat)





#### Exercise 2 ####

# Define the variables
tickers = c('AXP', 'MCD', 'GOOGL','XOM', 'IBM', 'NKE', 'WMT', 'KO','SPY')
from_date = '2009-1-1'
to_date = '2019-1-1'


# Get the data
getSymbols(Symbols = tickers, from = from_date, to = to_date, periodicity = 'daily', return.class = 'data.frame')

# Store the dates
dates = rownames(SPY)

# Function for computing returns
returnsCalc <- function(x){
  diff(x)/x[-length(x)]
}

# Function for calculating geometric mean
geomAveCalc <- function(x){
  (prod((1+x)))^(1/length(x))-1
}

# Store the Adjusted prices in a data frame
Adj.Prices = data.frame(Google = GOOGL$GOOGL.Adjusted, IBM = IBM$IBM.Adjusted, Nike = NKE$NKE.Adjusted, 
                        AmercianExpress = AXP$AXP.Adjusted, Walmart = WMT$WMT.Adjusted, Exxon = XOM$XOM.Adjusted,
                        CocaCola = KO$KO.Adjusted, McDonald = MCD$MCD.Adjusted, SP500 = SPY$SPY.Adjusted, 
                        row.names = dates)

# Compute daily returns
Daily.Returns = as.data.frame(apply(Adj.Prices, 2, FUN = returnsCalc))

# Compute expected market return and variance
market.mu = geomAveCalc(Daily.Returns$SP500)
market.sigma = var(Daily.Returns$SP500)


# Calculate beta for each stock using the definition of beta

betas = c()

for(daily_stock_ret in Daily.Returns[,1:length(tickers)-1]){
  beta = cov(daily_stock_ret, Daily.Returns$SP500)/market.sigma
  betas = cbind(betas, beta)
}
colnames(betas) = colnames(Daily.Returns)[1:8] 
betas

# Plot the historical average returns as a function of beta. Compute the average returns first

Avg.Returns = apply(Daily.Returns[,1:8], 2, geomAveCalc)

plot(betas, Avg.Returns, xlim = c(min(betas)-0.1, 1.5) ,ylim = c(0.00005, 0.0009),
     main = 'Historical average returns as a function of beta. CAPM shown as well with \n risk free rate = 0.02',
     cex.main = 1.2, cex.lab = 1.4)
text(betas, Avg.Returns+0.00005, labels = colnames(betas))

beta_plots = seq(0.4, 1.5, 0.01)
Rf = (1+0.02)^(1/252) -1
lines(beta_plots, Rf + beta_plots*(market.mu - Rf), col = 'blue', lwd = 2)

# Now Repeat the same thing but with weekly returns instead


# Get the weekly data
getSymbols(Symbols = tickers, from = from_date, to = to_date, periodicity = 'weekly', return.class = 'data.frame')

# Store the weekly dates
dates_weekly = rownames(SPY)


# Store the Adjusted prices in a data frame
Adj.Prices.Weekly = data.frame(Google = GOOGL$GOOGL.Adjusted, IBM = IBM$IBM.Adjusted, Nike = NKE$NKE.Adjusted, 
                        AmercianExpress = AXP$AXP.Adjusted, Walmart = WMT$WMT.Adjusted, Exxon = XOM$XOM.Adjusted,
                        CocaCola = KO$KO.Adjusted, McDonald = MCD$MCD.Adjusted, SP500 = SPY$SPY.Adjusted, 
                        row.names = dates_weekly)

# Compute weekly returns
Weekly.Returns = as.data.frame(apply(Adj.Prices.Weekly, 2, FUN = returnsCalc))

# Compute expected market return and variance
market.mu.weekly = geomAveCalc(Weekly.Returns$SP500)
market.sigma.weekly = var(Weekly.Returns$SP500)


# Calculate beta for each stock using the definition of beta

betas.weekly = c()

for(weekly_stock_ret in Weekly.Returns[,1:length(tickers)-1]){
  beta = cov(weekly_stock_ret, Weekly.Returns$SP500)/market.sigma.weekly
  betas.weekly = cbind(betas.weekly, beta)
}
colnames(betas.weekly) = colnames(Weekly.Returns)[1:8] 
betas.weekly


# Plot the historical average returns as a function of beta. Compute the average returns first

Avg.Returns.Weekly = apply(Weekly.Returns[,1:8], 2, geomAveCalc)

plot(betas.weekly, Avg.Returns.Weekly, xlim = c(min(betas)-0.1, 1.5) ,
     ylim = c(min(Avg.Returns.Weekly)-0.0005, max(Avg.Returns.Weekly) + 0.0009),
     main = 'Historical average returns as a function of beta for weekly returns. 
     CAPM shown as well with \n risk free rate = 0.02',
     cex.main = 1.2, cex.lab = 1.4)
text(betas.weekly, Avg.Returns.Weekly+0.0004, labels = colnames(betas.weekly))

beta_plots = seq(0.4, 1.5, 0.01)
Rf.Weekly = (1+0.02)^(1/52) -1
lines(beta_plots, Rf.Weekly + beta_plots*(market.mu.weekly - Rf.Weekly), col = 'blue', lwd = 2)


