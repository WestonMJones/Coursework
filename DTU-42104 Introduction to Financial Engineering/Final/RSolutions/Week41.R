### Week 41 Exercises for Introduction to Financial Engineering ###

# Load the library needed

library(quantmod)


# Define tickers and get data
tickers = c('MCD','KO')
getSymbols(tickers, from = '1991-1-1', to = '2001-1-1', periodicity = 'weekly', return.class = 'data.frame')


# Store Adjusted Close Prices for stocks in a single data frame
dates <- as.Date(rownames(MCD))
Prices <- data.frame(MCD=MCD$MCD.Adjusted, KO=KO$KO.Adjusted, row.names = dates)
head(Prices)


# Function for calculating continous returns & log returns
returnsCalc <- function(x){
  diff(x)/x[-length(x)]
}

# Compute the weekly returns
Returns <- apply(Prices, 2, returnsCalc)
head(Returns)

# Function for calculating geometric mean
geomAveCalc <- function(x){
  (prod((1+x)))^(1/length(x))-1
}

# Compute the weekly average return
weeklymean <- apply(Returns, 2, geomAveCalc)
weeklymean

# Annualize the averages
yearlymean <- ((1+weeklymean)^52-1)
yearlymean

# Compute the covariance matrix and annualize it
Covariance_mat = cov(Returns) * 52
Covariance_mat

# Function for computing minimum variance portfolios without risk free asset
minVarPort = function(mu, Sigma, mu_p){
  n = length(mu)
  A = t(cbind(mu, rep(1,n))) %*% solve(Sigma) %*% t(t(cbind(mu, rep(1,n))))
  
  opt_weights = solve(Sigma) %*% (cbind(mu, rep(1,n))) %*% solve(A) %*% t(t(c(mu_p, 1)))
  opt_var = (t(c(mu_p, 1))) %*% solve(A) %*% t(t(c(mu_p, 1)))
  return(list(weights = opt_weights, variance = opt_var, port_return = mu_p))
}

# Compute the efficient frontier without risk free asset
opt_w1 = c()
opt_var1 = c()
mup = seq(min(yearlymean)-0.05, max(yearlymean)+0.05, 0.002)
for (mu_p in mup){
  opt_port = minVarPort(yearlymean, Covariance_mat, mu_p)
  opt_w1 = cbind(opt_w1, opt_port$weights)
  opt_var1 = rbind(opt_var1, opt_port$variance)
}  

plot(opt_var1^0.5, mup, lwd =3, type='l', xlab = 'Portfolio Standard Deviation', ylab = 'Portfolio Return', 
     main ='Efficient Frontier of McDonalds and Coca-Cola', ylim = c(0.01, 0.5))
grid()


# Function for computing optimal portfolios with risk free asset included
minVarPort_Rf = function(mu, Sigma, mu_p, Rf){
  InvSigma = solve(Sigma)
  mu_e = t(t(mu - Rf))
  opt_weights = (InvSigma %*% mu_e) * as.numeric((mu_p / (t(mu_e) %*% InvSigma %*% mu_e)))
  opt_var = (mu_p^2) / (t(mu_e) %*% InvSigma %*% mu_e)
  w_0 = 1 - t(opt_weights) %*% t(t(rep(1, length(mu_e))))
  opt_weights = rbind(opt_weights, w_0)
  return(list(weights = opt_weights, variance = opt_var, port_return = mu_p))
}


# Set up the new variables to store the optimal weights and variances
opt_w2 = c()
opt_var2 = c()
Rf = 0.02
mup = seq(min(yearlymean)-0.05, max(yearlymean)+0.05, 0.002) - Rf

# Compute the CML with the risk free asset
for (mu_p in mup){
  opt_port = minVarPort_Rf(yearlymean, Covariance_mat, mu_p, Rf = Rf)
  opt_w2 = cbind(opt_w2, opt_port$weights)
  opt_var2 = rbind(opt_var2, opt_port$variance)
}  

plot(opt_var1^0.5, mup, lwd =3, type='l', xlab = 'Portfolio Standard Deviation', ylab = 'Portfolio Return', 
     main ='Efficient Frontier of McDonalds and Coca-Cola along with CML')
grid()
lines(opt_var2^0.5, mup, col = 'blue', lwd = 3)


### 1.b) Now we redo all of this except we add Microsoft into the situation as well ### 

# Define tickers and get data
tickers = c('MCD','KO','MSFT')
getSymbols(tickers, from = '1991-1-1', to = '2001-1-1', periodicity = 'weekly', return.class = 'data.frame')


# Store Adjusted Close Prices for stocks in a single data frame
dates <- as.Date(rownames(MCD))
Prices <- data.frame(MCD=MCD$MCD.Adjusted, KO=KO$KO.Adjusted, MSFT = MSFT$MSFT.Adjusted, row.names = dates)
head(Prices)

# Compute the weekly returns
Returns <- apply(Prices, 2, returnsCalc)
head(Returns)

# Compute the weekly average return
weeklymean_2 <- apply(Returns, 2, geomAveCalc)
weeklymean_2

# Annualize the averages
yearlymean_2 <- ((1+weeklymean_2)^52-1)
yearlymean_2

# Compute the covariance matrix and annualize it
Covariance_mat_2 = cov(Returns) * 52
Covariance_mat_2



# Compute the efficient frontier without risk free asset but microsoft included
opt_w_No_Rf = c()
opt_var_No_Rf = c()
mup2 = seq(min(yearlymean_2)-0.05, max(yearlymean_2)+0.05, 0.002)
for (mu_p in mup2){
  opt_port = minVarPort(yearlymean_2, Covariance_mat_2, mu_p)
  opt_w_No_Rf = cbind(opt_w_No_Rf, opt_port$weights)
  opt_var_No_Rf = rbind(opt_var_No_Rf, opt_port$variance)
} 


# Compute the CML with the risk free asset and microsoft included
opt_w_Rf = c()
opt_var_Rf = c()
Rf = 0.02
mup2 = seq(min(yearlymean_2)-0.05, max(yearlymean_2)+0.05, 0.002) - Rf

# Compute the CML with the risk free asset
for (mu_p in mup2){
  opt_port = minVarPort_Rf(yearlymean_2, Covariance_mat_2, mu_p, Rf = Rf)
  opt_w_Rf = cbind(opt_w_Rf, opt_port$weights)
  opt_var_Rf = rbind(opt_var_Rf, opt_port$variance)
}  


plot(opt_var1^0.5, mup, lwd =3, type='l', xlab = 'Portfolio Standard Deviation', ylab = 'Portfolio Return', 
     main ='Efficient Frontier of McDonalds and Coca-Cola along with CML', ylim = c(0.15, 0.33))
grid()
lines(opt_var2^0.5, mup, col = 'blue', lwd = 3)

lines(opt_var_No_Rf^0.5, mup2, col = 'Red', lwd = 3)
lines(opt_var_Rf^0.5, mup2, col ='Green', lwd = 3)

legend('topright', legend = c('Efficient Frontier w/o MSFT', 'CML w/o MSFT','Efficient Frontier w/ MSFT','CML w/ MSFT'),
       lty = c(1,1,1,1), col = c('black','blue','red','green'), lwd = 3)



### EXERICSE 2 ###

# Load the necessary package to solve quadratic programs as we will be using this for computing 
# the weights where no short selling is allowed

library(quadprog)
library(Rsolnp)

minVarPort_No_Shorting_No_Rf = function(mu, Sigma, mu_p){
  
  # Define the optimization problem 
  n = length(mu)
  Dmat = Sigma
  dvec = t(t(rep(0, n)))
  Amat = matrix(0, nrow = n, ncol = n+2)
  Amat[,1] = mu
  Amat[,2] = 1
  Amat[, 3:(n+2)] = diag(rep(1,n))
  bvec = c(mu_p, 1,rep(0, n))
  
  opt_results = solve.QP(Dmat = Dmat, dvec = dvec, Amat = Amat, bvec = bvec, meq = 2)
  return(list(weights = opt_results$solution, variance = 2*opt_results$value, port_return = mu_p))
}


opt_port_return_no_Rf = c()
opt_w_No_Short_No_Rf = c()
opt_var_No_Short_No_Rf = c()

mus =  seq(min(yearlymean_2), max(yearlymean_2), 0.002)
for (mu_p in mus){
  opt_port = minVarPort_No_Shorting_No_Rf(yearlymean_2, Covariance_mat_2, mu_p)
  opt_w_No_Short_No_Rf = cbind(opt_w_No_Short_No_Rf, opt_port$weights)
  opt_var_No_Short_No_Rf = rbind(opt_var_No_Short_No_Rf, opt_port$variance)
  opt_port_return_no_Rf = cbind(opt_port_return_no_Rf, opt_port$port_return)
}  

plot(opt_var_No_Short_No_Rf^0.5, opt_port_return_no_Rf, lwd = 5, type='l', xlab = 'Portfolio Standard Deviation', 
     ylab = 'Portfolio Return', main= 'Efficient frontiers for various constraints', ylim = c(0.15,0.36), xlim = c(0.15,0.4))

#lines(opt_var1^0.5, mup, lwd = 3, col = 'green')

# Process of defining the optimization problem with risk-free lending but no shorting

# Objective function 
CalcVar=function(w, Sigma, mu, Rf)
{
  Sigma[1,1]* w[1]^2 + Sigma[2,2]* w[2]^2 + Sigma[3,3] * w[3]^2 +
    2*w[1]*w[2]*Sigma[1,2] + 
    2*w[1]*w[3]*Sigma[1,3] + 
    2*w[2]*w[3]*Sigma[2,3]
}

# Equality Constraints (Left hand side)
eq_left2=function(w, Sigma, mu, Rf){
  z1 = w[1]+ w[2] + w[3] + w[4]
  z2 = mu[1]*w[1] + mu[2]*w[2] + mu[3]*w[3] + w[4]*Rf
  return(c(z1,z2))
}

# Inequality constratins as lowerbounds of elements
lb = c(0, 0, 0, 0)

# Inequality constraints as upperbounds of elements

#Initial guess
x0 = c(.1,.1,.7,.1)


opt_w_Rfl = c()
opt_var_Rfl = c()
opt_port_return_rf = c()
Rf_l = 0.02
mus =  seq(min(yearlymean_2), max(yearlymean_2), 0.002) - Rf_l
for(expected_return in mus){
  opt_sol = solnp(pars = x0, fun = CalcVar, eqfun = eq_left2, eqB = c(1, expected_return) , LB = lb,
        Sigma = Covariance_mat_2, mu = yearlymean_2- Rf_l, Rf = Rf_l)
  
  opt_w_Rfl = rbind(opt_w_Rfl, opt_sol$pars)
  opt_var_Rfl = rbind(opt_var_Rfl, opt_sol$values[length(opt_sol$values)])
  opt_port_return_rf = rbind(opt_port_return_rf, expected_return + Rf_l)
}

lines(opt_var_Rfl^0.5, opt_port_return_rf, lwd = 3, col = 'red')


# Function that only allows for maximum of 1/2 wealth allocation into 1 asset
minVarPort_max_half_wealth = function(mu, Sigma, mu_p){
  
  # Define the optimization problem 
  n = length(mu)
  Dmat = Sigma
  dvec = rep(0, n)
  Amat = matrix(0, nrow = n, ncol = n+2)
  Amat[,1] = mu
  Amat[,2] = 1
  Amat[, 3:(n+2)] = diag(rep(-1,n))
  bvec = c(mu_p, 1 ,rep(-0.5, n))
  
  opt_results = solve.QP(Dmat = Dmat, dvec = dvec, Amat = Amat, bvec = bvec, meq = 2)
  return(list(weights = opt_results$solution, variance = 2*opt_results$value, port_return = mu_p))
}


#install.packages('testit')  Is used for the has_error function
#library(testit)

# Compute the efficient frontier when only 50% of your wealth is allowed to be allocated into a single asset
opt_w_max_half = c()
opt_var_max_half = c()
opt_port_return = c()

# Compute the lowest and highest possible portfolio returns
MinRet = mean(sort(yearlymean_2)[1:2])
MaxRet = mean(sort(yearlymean_2, decreasing = TRUE)[1:2])
for(return in seq(MinRet,MaxRet,0.002)){
    opt_results = minVarPort_max_half_wealth(yearlymean_2, Covariance_mat_2, return)
    opt_w_max_half = rbind(opt_w_max_half, opt_results$weights)
    opt_var_max_half = rbind(opt_var_max_half, opt_results$variance)
    opt_port_return = rbind(opt_port_return, return)
}

#plot(opt_var_max_half^0.5, opt_port_return, lwd = 3, type = 'l', xlab = 'Portfolio Standard Deviation',
#     ylab = 'Portfolio Return', main= 'Efficient Frontier when only max of 50% your wealth is allowed into 1 asset ')

lines(opt_var_max_half^0.5, opt_port_return, lwd =3, col='blue')
lines(opt_var_No_Rf^0.5, mup2+0.02, lwd = 2, col ='yellow')
lines(opt_var_Rf^0.5, mup2+0.02, lwd = 2, col ='green')


legend('topleft', legend = c('No risk-free lending & SS', 'W/ RF-lending but w/o SS','Max 50% allocation pr asset',
                             'w/ SS', 'w/ RF and SS'), 
       lty = c(1,1,1,1,1), col = c('black','red','blue','yellow','green'), lwd = 3)














