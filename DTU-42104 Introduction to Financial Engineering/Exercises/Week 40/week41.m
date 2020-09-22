opts = delimitedTextImportOptions("NumVariables", 7);

% Specify range and delimiter
opts.DataLines = [2, Inf];
opts.Delimiter = ",";

% Specify column names and types
opts.VariableNames = ["Date", "Open", "High", "Low", "Close", "AdjClose", "Volume"];
opts.VariableTypes = ["datetime", "double", "double", "double", "double", "double", "double"];
opts = setvaropts(opts, 1, "InputFormat", "yyyy-MM-dd");
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Import the data
Coke = readtable("C:\Users\Westo\Desktop\FinancialEngineering\Exercises\Week 40\Coke.csv", opts);
McDonalds = readtable("C:\Users\Westo\Desktop\FinancialEngineering\Exercises\Week 40\McDonalds.csv", opts);
Microsoft = readtable("C:\Users\Westo\Desktop\FinancialEngineering\Exercises\Week 40\Microsoft.csv", opts);

% Calculate weekly returns
CokeWeeklyReturns = (Coke.AdjClose(2:end)-Coke.AdjClose(1:end-1))./Coke.AdjClose(1:end-1);
McDonaldsWeeklyReturns = (McDonalds.AdjClose(2:end)-McDonalds.AdjClose(1:end-1))./McDonalds.AdjClose(1:end-1);
MicrosoftWeeklyReturns = (Microsoft.AdjClose(2:end)-Microsoft.AdjClose(1:end-1))./Microsoft.AdjClose(1:end-1);

% Calculate average returns
CokeAverageReturn = prod(1+CokeWeeklyReturns)^(1/size(CokeWeeklyReturns,1))-1;
McDonaldsAverageReturn = prod(1+McDonaldsWeeklyReturns)^(1/size(McDonaldsWeeklyReturns,1))-1;
MicrosoftAverageReturn = prod(1+MicrosoftWeeklyReturns)^(1/size(MicrosoftWeeklyReturns,1))-1;

%Annualize returns
CokeAnnualAverageReturn = (1+CokeAverageReturn)^52-1;
McDonaldsAnnualAverageReturn = (1+McDonaldsAverageReturn)^52-1;
MicrosoftAnnualAverageReturn = (1+MicrosoftAverageReturn)^52-1;

% Calculate Standard deviation
CokeStdReturns = std(CokeWeeklyReturns);
CokeAnnualStdReturns = sqrt(52)*CokeStdReturns;

McDonaldsStdReturns = std(McDonaldsWeeklyReturns);
McDonaldsAnnualStdReturns = sqrt(52)*McDonaldsStdReturns;

MicrosoftStdReturns = std(MicrosoftWeeklyReturns);
MicrosoftAnnualStdReturns = sqrt(52)*MicrosoftStdReturns;

% Variance mtx
VarCov = cov([McDonaldsWeeklyReturns CokeWeeklyReturns MicrosoftWeeklyReturns]);
Corr = corr([McDonaldsWeeklyReturns CokeWeeklyReturns MicrosoftWeeklyReturns]);
VarCovAnn = 52*cov([McDonaldsWeeklyReturns CokeWeeklyReturns MicrosoftWeeklyReturns]);

% Portfolio Calculation -- order is McDs, Coca Cola, Microsoft
% (0, 0, 1),(0, 0.1, 0.9),(0.1, 0.1, 0.8). . . ,(0.9, 0.1, 0),(1, 0, 0)

portfolios = zeros(66, 3);
portfolioReturns = [];
portfolioDeviations = [];
portfolioRatios = [];
count = 0;

u = [McDonaldsAnnualAverageReturn; CokeAnnualAverageReturn; MicrosoftAnnualAverageReturn];

for a=0:10
    for b=0:10-a
            c=10-a-b;
                      
            count = count + 1; 
           
            w = [a / 10;b / 10;c / 10;];
            
            
            
            
            portfolios(count,:) = w;         
            portfolioReturns(count) = transpose(w)*u;
            portfolioVariance(count) = transpose(w)*VarCovAnn*w;
            portfolioRatios(count) = portfolioReturns(count) / portfolioVariance(count);
            
        
    end
end

scatter(portfolioVariance,portfolioReturns)

max(portfolioReturns)
min(portfolioVariance)
max(portfolioRatios)

% 1st has the highest mean --  0.3524
% 43rd has the lowest stdev --  0.0377
% 42nd has the highest ratio --  6.1506

%%% Part 2
