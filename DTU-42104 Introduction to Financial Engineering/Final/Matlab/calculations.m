%% Data from NASDAQ - See appendix in report
TODAY = datenum(2019,09,19);
Names = ["DGBI 2023 GB";"1,5ST.I.23 GB";"3ST.I. 21 GB";"4,5 St.I 39 GB";"4St.I. 19 GB";"DANSKE STAT 2022";"DANSKE STAT 2029";"DGBi";"Danske Stat 2020";"Danske Stat 2025";"Danske Stat 2027";"7 St.I 24 GB"];
CleanPrices = [106.950; 109.600; 108.250; 199.540; 100.833; 103.860; 110.350; 122.150; 101.304; 115.270; 109.738; 140.480];
Coupons = [0.10; 1.50; 3.00; 4.50; 4.00; 0.25; 0.50; 0.10; 0.25; 1.75; 0.50; 7.00];
MaturityYears = [2023; 2023; 2021; 2039; 2019; 2022; 2029; 2030; 2020; 2025; 2027; 2024;];
MaturityDates = datenum(MaturityYears , 11, 15);

%% Convert Clean Prices to Dirty Prices
InterestAccrued = yearfrac(datenum(2018,11,15), TODAY,0) .* Coupons;
DirtyPrices = CleanPrices + InterestAccrued;

%% Yields
for j = 1:length(Names)
    Payments = Coupons(j) * ones(year(datenum(MaturityYears(j),11,15)-TODAY)+1, 1);
    Payments(end) = Payments(end) + 100;
    PaymentTimestamp = 0; % reset array
    for i = year(TODAY):MaturityYears(j)
        PaymentTimestamp(i-year(TODAY)+1) = datenum(i, 11, 15);
    end
    
    Yield(j) = cfyield(Payments',PaymentTimestamp,DirtyPrices(j),TODAY);
end

figure(1)
scatter(MaturityYears,Yield*100)
ylabel('bp')
xlabel('Maturity')

%% Nelson-Siegel Term structure
x = yearfrac(TODAY, MaturityDates([2:4 6:7 9:12]));
y = Yield([2:4 6:7 9:12]);
[x, order] = sort(x);
y = y(order)*100;
par = nelsonfit(x,y);
p = nelsonfun(0:0.25:30,par);
figure(2)
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

%% Duration - Using the Fisher-Weil equation
for j = 1:length(Names)
    %Yields = nelsonfun(TimeToPayments,par);
    for i = year(TODAY):MaturityYears(j)
        %Yields 
    end
end

%% Selecting Portfolio
StudentNumbers = 1+9+1+3+7+9+1+8+0+2+2+5+1+9+1+3+8+0;
StudentNumbers = 7;
X = 5 + .5* StudentNumbers;