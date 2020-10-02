% Prices from Sep 2 (or around there)
TODAY = datenum(2019,9,2);
Price = [110.41 108.8 204.83  100.85 141.93  103.86  112.31  107.52 122.15 101.42 116.82 110.96 ];
Coupon = [1.5 3 4.5  4 7 0.25 0.5 0.1 0.1 0.25 1.75 0.5 ];
MatYear = [2023 2021 2039  2019 2024 2022 2029 2023 2030 2020 2025 2027 ];
CalcDate = datenum(2019,9,2);
for i = 1:12
Maturity(i) = datenum(MatYear(i),11,15); % find maturity dates
end

% Find yields
for j = 1:12
    clearvars TimeOfPayments TimeToPayments Payment
        for i = year(TODAY):year(Maturity(j)) 
            TimeOfPayments(i-year(TODAY)+1,1) = datenum(i,11,15);
            TimeToPayments(i-year(TODAY)+1,1) = yearfrac(TODAY,datenum(i,11,15),0);
            Payment(i-year(TODAY)+1,1) = Coupon(j);
        end

Payment(end,1) = 100+Payment(end,1); % add principal to last payment

AccruedInterest = yearfrac(datenum(year(TODAY)-1,11,15),CalcDate,0)*Coupon(j);

DirtyPrice(j) = AccruedInterest + Price(j);

Yield(j) = cfyield(Payment',TimeOfPayments',DirtyPrice(j),TODAY); % Check with programming yourself using fzero.

CalcPV(Yield(j),TimeToPayments,Payment);

fun = @(x) CalcPV(x,TimeToPayments,Payment)-DirtyPrice(j);
YieldProgrammed(j) = fzero(fun,0); % Should give the same as Matlab's function
end

scatter(MatYear,Yield*100)
ylabel('bp')
xlabel('Maturity')
close

% Fit Nelson-Siegel as of Sep 2 - the index bonds are removed
x = yearfrac(CalcDate, Maturity([1:7 10:12]));
y = Yield([1:7 10:12]);
[x, order] = sort(x);
y = y(order)*100;
par = nelsonfit(x,y);
p = nelsonfun(0:0.25:30,par);
figure
set(gcf,'Color','w')
plot(x,y,'-rs'); hold on
plot(0:0.25:30,p,'-g' )
title('Nelson-Siegel approximation:')
xlabel('Maturity, years')
legend('DK yield curve (as of Sep 2019)', ...
      ['NS(\beta_{0} = '  sprintf('%3.2f',par.beta(1)) ',' ...
           '\beta_{1} = ' sprintf('%3.2f',par.beta(2)) ',' ...
           '\beta_{2} = ' sprintf('%3.2f',par.beta(3)) ',' ...
           '\tau = '      sprintf('%3.2f',par.tau)     ')'])
legend(gca,'boxoff')
close

for j = [1:7 10:12]
    clearvars TimeOfPayments TimeToPayments Payment
        for i = year(TODAY):year(Maturity(j))
            TimeOfPayments(i-year(TODAY)+1,1) = datenum(i,11,15);
            TimeToPayments(i-year(TODAY)+1,1) = yearfrac(CalcDate,datenum(i,11,15),0);
            Payment(i-year(TODAY)+1,1) = Coupon(j);
        end

Payment(end,1) = 100+Payment(end,1);

AccruedInterest = yearfrac(datenum(year(TODAY)-1,11,15),CalcDate,0)*Coupon(j);

DirtyPrice(j) = AccruedInterest + Price(j);

Yields = nelsonfun(TimeToPayments,par);

ModDuration(j) = sum(TimeToPayments.*Payment./((1+Yield(j)).^(1+TimeToPayments)));
ModDuration(j) = ModDuration(j)/DirtyPrice(j);
MacDuration(j) = ModDuration(j)*((1+Yield(j)));
FWDuration(j) = sum(TimeToPayments.*Payment./((1+Yields/100).^(1+TimeToPayments)));
FWDuration(j) = FWDuration(j)/DirtyPrice(j);
FWConvexity(j) = sum(TimeToPayments(:,1).*(TimeToPayments(:,1)+1).*Payment./((1+Yields/100).^(2+TimeToPayments(:,1))));
FWConvexity(j) = FWConvexity(j)/DirtyPrice(j);
end

