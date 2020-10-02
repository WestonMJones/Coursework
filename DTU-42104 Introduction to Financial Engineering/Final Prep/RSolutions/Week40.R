
#Week 40 42104 Introduction to Financial Engineering

#################PART1#################

library(quantmod)


# Define tickers and get data
tickers = c('MCD','KO','MSFT')
getSymbols(tickers, from = '1991-1-1', to = '2001-1-1', periodicity = 'weekly', return.class = 'data.frame')


# Store Adjusted Close Prices for stocks in a single data frame
dates <- as.Date(rownames(MCD))
Prices <- data.frame(MCD=MCD$MCD.Adjusted, KO=KO$KO.Adjusted, MSFT=MSFT$MSFT.Adjusted, row.names = dates)
head(Prices)


# Function for calculating continous returns & log returns
returnsCalc <- function(x){
  diff(x)/x[-length(x)]
}

Returns <- apply(Prices, 2, returnsCalc)
head(Returns)

# Function for calculating geometric mean
geomAveCalc <- function(x){
  (prod((1+x)))^(1/length(x))-1
}

weeklymean <- apply(Returns, 2, geomAveCalc)

# Weekly return in %
weeklymean*100


yearlymean <- ((1+weeklymean)^52-1)

# Yearly return in %
yearlymean*100

yearlycov <- 52 * cov(Returns)
yearlycov

# Now think about a portfolio  p is such that in total p_1 + p_2 + p_3 = 1 and we look at the following
# combinations of the form (0.1, 0.1, 0.8), (0.1, 0.2, 0.7) and so forth

# Create a matrix of portfolio weights
#totNumbPort <- 11+10+9+8+7+6+5+4+3+2+1 # Total number of portfolios

portfolios = matrix(0, nrow = 1, ncol = 3)
port_mean <- c()
port_var <- c()
port_std <- c()

count = 1
for (i in seq(1,0,-0.1)){
  for (j in seq(1-i, 0, -0.1)){
    k = 1-i-j
    current_portfolio = c(i,j,k)
    portfolios = rbind(portfolios, current_portfolio)  # Store the portfolio
    port_mean[count] <- t(current_portfolio) %*% yearlymean 
    port_var[count] <- t(current_portfolio) %*% yearlycov %*% current_portfolio
    port_std[count] <- sqrt(port_var[count])
    count = count + 1
  }
}
portfolios
port_mean
port_var
port_std

# Plot portfolios
plot(port_std, port_mean, xlab = 'standard deviation', ylab = 'mean', main = 'Portfolio Performance')

# Highest expected return
max_r <-  match(max(port_mean),port_mean) # Find portfolio with highest return
portfolios[max_r+1, ]

# Plot highest return on plot
points(port_std[max_r], port_mean[max_r], col = 'red', pch=8, cex=3)

# Lowest standard deviation
min_std <-  match(min(port_std),port_std) # Find portfolio with the lowest standard deviation
portfolios[min_std, ]

# Plot lowest standard deviation
points(port_std[min_std], port_mean[min_std], col = 'blue', pch=8, cex=3)

# Highest slope (Sharpe Ratio)
port_sharpe = port_mean / port_std

max_slope = match(max(port_sharpe), port_sharpe)
portfolios[max_slope, ]

# Plot max Sharpe Ratio on plotdeviation
points(port_std[max_slope], port_mean[max_slope], col = 'green', pch=8, cex=3)


#################PART2#################


minVarPort = function(mu, Sigma, mu_p){
  n = length(mu)
  A = t(cbind(mu, rep(1,n))) %*% solve(Sigma) %*% t(t(cbind(mu, rep(1,n))))
  
  opt_weights = solve(Sigma) %*% (cbind(mu, rep(1,2))) %*% solve(A) %*% t(t(c(mu_p, 1)))
  opt_var = (t(c(mu_p, 1))) %*% solve(A) %*% t(t(c(mu_p, 1)))
  return(list(weights = opt_weights, variance = opt_var, port_return = mu_p))
}


# Asset 1:  R_1 = 10%,  sigma_1 = 10%
# Asset 2 : R_2 = 20%,  sigma_2 = 20%
# Need to find the covariance matrix for the following correlations: rho = 0, rho = 0.5, rho = -0.5

# Just define the variables that we are given
R_1 = 0.1
R_2 = 0.2

sd_1 = 0.1
sd_2 = 0.2

var_1 = sd_1^2
var_2 = sd_2^2

# Compute the off-diagonal element
cov_12 = 0.5 * 0.1*0.2

# Construct the 3 different covariance matrices
Sigma_0 = diag(c(sd_1^2,sd_2^2))
Sigma_pos = matrix(c(var_1, cov_12, cov_12, var_2), nrow = 2, ncol = 2)
Sigma_neg = matrix(c(var_1, -cov_12, -cov_12, var_2), nrow = 2, ncol = 2)

mu = matrix(c(R_1,R_2), nrow = 2, ncol = 1)

opt_w1 = c()
opt_var1 = c()
for (mu_p in seq(0.05, 0.5, 0.01)){
  opt_port = minVarPort(mu, Sigma_0, mu_p)
  opt_w1 = cbind(opt_w1, opt_port$weights)
  opt_var1 = rbind(opt_var1, opt_port$variance)
  
}

opt_w2 = c()
opt_var2 = c()
for (mu_p in seq(0.05, 0.5, 0.01)){
  opt_port = minVarPort(mu, Sigma_pos, mu_p)
  opt_w2 = cbind(opt_w2, opt_port$weights)
  opt_var2 = rbind(opt_var2, opt_port$variance)
}

opt_w3 = c()
opt_var3 = c()
for (mu_p in seq(0.05, 0.5, 0.01)){
  opt_port = minVarPort(mu, Sigma_neg, mu_p)
  opt_w3 = cbind(opt_w3, opt_port$weights)
  opt_var3 = rbind(opt_var3, opt_port$variance)
}


plot(opt_var1^0.5 ,seq(0.05, 0.5, 0.01), type = 'o', lwd = 2, xlab = 'Portfolio Standard deviation'
     , ylab = 'Portfolio Return', main = 'Efficient Frontier for rho = 0, 0.5, -0.5')

lines(opt_var2^0.5 ,seq(0.05, 0.5, 0.01), type = 'o', lwd = 2, col = 'red')

lines(opt_var3^0.5 ,seq(0.05, 0.5, 0.01), type = 'o', lwd = 2, col = 'blue')
legend('topleft', legend = c('rho = 0', 'rho = 0.5', 'rho = -0.5'), col = c('Black','red','blue'),
       lty = 1, lwd = 2)

# What happens when rho -> 1, means we got a singular covariance matrix. This means we cannot solve this optimizing
# problem. See for yourself that it is in fact singular as the determinant is 0.

# Try for different values for rho and see how it affects the effiecient frontier
rho = 0.95
Sigma_1 = matrix(c(var_1, 0.1*0.2*rho, 0.1*0.2*rho, var_2), nrow = 2, ncol = 2)
Sigma_1
det(Sigma_1)

opt_w4 = c()
opt_var4 = c()
for (mu_p in seq(0.05, 0.5, 0.01)){
  opt_port = minVarPort(mu, Sigma_1, mu_p)
  opt_w4 = cbind(opt_w4, opt_port$weights)
  opt_var4 = rbind(opt_var4, opt_port$variance)
}

# uncomment this to see the efficient frontier for changing values of correlation and what happens when rho -> +-1
#lines(opt_var4^0.5 ,seq(0.05, 0.5, 0.01), type = 'o', lwd = 2, col = 'green')

# Plot the portfolios we constructed back in exercise 1) on top of the optimal portoflios we found
points(port_std, port_mean, xlab = 'standard deviation', ylab = 'mean', main = 'Portfolio Performance')


