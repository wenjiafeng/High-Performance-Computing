
Worker=[1 2 3 4];
Time=[34.7400 12.5621 8.7544 6.8688];
Speedup=[1 2.7657 3.9683 5.0591];
y3=[1 2 3 4];
yyaxis left
plot(Worker,Time);
ylabel('Time (Seconds)');
yyaxis right
plot(Worker,Speedup);hold on;
plot(x,y3,'-.');
legend('Time','Speedup','Linear');
ylabel('Speedup');
xlabel('Worker number');
