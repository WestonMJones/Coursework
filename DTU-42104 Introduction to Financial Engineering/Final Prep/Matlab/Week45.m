clear
Tickers = {'MCD' 'KO', 'MSFT'};
StockData = hist_stock_data('01011991', '01012001', Tickers, 'frequency','wk');
PlotNames = strcat(pwd,'\Figures\'); % make sure subdirectory exists

MarketData = hist_stock_data('01011994', '01012001', 'SPY', 'frequency','wk');
MarketReturn = diff(MarketData(1).AdjClose)./MarketData(1).AdjClose(1:end-1);

NoStocks = size(Tickers,2);

% a) Calc returns
for i = 1:NoStocks
    ReturnMatrix(:,i) = diff(StockData(i).AdjClose)./StockData(i).AdjClose(1:end-1); %#ok<*SAGROW>
end

T = size(ReturnMatrix,1);


% Analysing data
for i=1:NoStocks
    mu(i,1) = prod(1+ReturnMatrix(:,i))^(1/T)-1;
    mu(i,1) = (mu(i,1)+1)^52-1;
end

SIGMA = cov(ReturnMatrix)*52;
StDev = diag(SIGMA).^0.5;
SharpeRatio = (mu-0.02)./StDev;

% S&P data
mu_SP(1,1) = prod(1+MarketReturn(:,1))^(1/T)-1;
mu_SP(1,1) = (mu_SP(1,1)+1)^52-1;
sigma_SP = (cov(MarketReturn)*52)^0.5;

% Efficient frontier
EF.mu = mu;
EF.rf = 0.02;
EF.a = mu'/SIGMA*mu;
EF.b = mu'/SIGMA*ones(size(mu,1),1);
EF.c = ones(size(mu,1),1)'/SIGMA*ones(size(mu,1),1);
EF.A = [[EF.a EF.b];[EF.b EF.c];];
SigmaInv = inv(SIGMA);
EF.ParabolaCoeff = [EF.a/(EF.a*EF.c-EF.b^2) -2*EF.b/(EF.a*EF.c-EF.b^2) EF.c/(EF.a*EF.c-EF.b^2)];
EF.w = SigmaInv*[mu ones(size(mu,1),1)]/EF.A;


EF.mu_gmv = EF.b/EF.c;
EF.sigma_gmw = (1/EF.c)^0.5;
EF.w_gmw = (1/EF.c)*SigmaInv*ones(size(mu,1),1);

EF.mu_e_tan = [];
mu_e = mu-ones(size(mu,1),1)*EF.rf;
EF.mu_e_tan = (mu_e'/SIGMA*mu_e)/(ones(size(mu,1),1)'/SIGMA*mu_e);
EF.mu_tan = EF.mu_e_tan+EF.rf;
EF.sigma_tan = EF.mu_e_tan/sqrt(mu_e'/SIGMA*mu_e);
EF.w_tan = EF.mu_e_tan/(mu_e'/SIGMA*mu_e)*SigmaInv*mu_e;
EF.slope = 1/sqrt(mu_e'/SIGMA*mu_e);
    



Portfolios(:,1) = EF.w_gmw;
Portfolios(:,2) = EF.w_tan;

mu_goal = 0.25;
alpha = mu_goal - EF.mu_gmv;
alpha = alpha/(EF.mu_tan-EF.mu_gmv);
alpha = 1-alpha;

%It's the same!
w_goal(:,1) = EF.w*([mu_goal 1]');
w_goal(:,2) = (alpha)*Portfolios(:,1) + (1-alpha)*Portfolios(:,2);

cov = Portfolios(:,2)'*SIGMA;

Ratio= (mu-0.02)./cov';

Ratio_tan = ones(1,NoStocks)*inv(SIGMA)*(mu-0.02);

Tickers = {'AXP' 'MCD', 'GOOGL', 'XOM', 'IBM' 'NKE' 'WMT' 'KO'};
StockData = hist_stock_data('01012009', '01012019', Tickers, 'frequency','wk');

MarketData = hist_stock_data('01012009', '01012019', 'SPY' , 'frequency','wk');
MarketReturn_w = diff(MarketData(1).AdjClose)./MarketData(1).AdjClose(1:end-1);

NoStocks = size(Tickers,2);

% a) Calc returns
for i = 1:NoStocks
    ReturnCAPM_w(:,i) = diff(StockData(i).AdjClose)./StockData(i).AdjClose(1:end-1); %#ok<*SAGROW>
end

T = size(ReturnCAPM_w,1);

for i = 1:8
    mdl = LinearModel.fit(MarketReturn_w,ReturnCAPM_w(:,i));
    alpha_w(i) = mdl.Coefficients.Estimate(1);
    betaCAPM_w(i) = mdl.Coefficients.Estimate(2);
    specific(i) = mdl.MSE;
end

for i=1:8
    muCAPM_w(i,1) = prod(1+ReturnCAPM_w(:,i))^(1/T)-1;
    muCAPM_w(i,1) = (muCAPM_w(i,1)+1)^52-1;
end
 
scatter(betaCAPM_w, muCAPM_w)

mdl = LinearModel.fit(betaCAPM_w,muCAPM_w);
intercept_w = mdl.Coefficients.Estimate(1);
slope_w = mdl.Coefficients.Estimate(2);
hold on
plot([ 0 betaCAPM_w 2],intercept_w + [0 betaCAPM_w 2]*slope_w)
close

Tickers = {'AXP' 'MCD', 'GOOGL', 'XOM', 'IBM' 'NKE' 'WMT' 'KO'};
StockData = hist_stock_data('01012009', '01012019', Tickers);

MarketData = hist_stock_data('01012009', '01012019', 'SPY');
MarketReturn = diff(MarketData(1).AdjClose)./MarketData(1).AdjClose(1:end-1);

NoStocks = size(Tickers,2);

% a) Calc returns
for i = 1:NoStocks
    ReturnCAPM(:,i) = diff(StockData(i).AdjClose)./StockData(i).AdjClose(1:end-1); %#ok<*SAGROW>
end

T = size(ReturnCAPM,1);

for i = 1:8
    mdl = LinearModel.fit(MarketReturn,ReturnCAPM(:,i));
    alpha(i) = mdl.Coefficients.Estimate(1);
    betaCAPM(i) = mdl.Coefficients.Estimate(2);
    specific(i) = mdl.MSE;
end

for i=1:8
    muCAPM(i,1) = prod(1+ReturnCAPM(:,i))^(1/T)-1;
    muCAPM(i,1) = (muCAPM(i,1)+1)^252-1;
end
 
scatter(betaCAPM, muCAPM)

mdl = LinearModel.fit(betaCAPM,muCAPM);
intercept = mdl.Coefficients.Estimate(1);
slope = mdl.Coefficients.Estimate(2);
hold on
plot([ 0 betaCAPM 2],intercept + [0 betaCAPM 2]*slope)










