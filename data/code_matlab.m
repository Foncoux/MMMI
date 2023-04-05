clc
clear all
close all

% %% enregistrer les données dans les fichiers .txt
% A = xlsread('data_projet_prog.xlsx')';
% hosp = A(1,:);
% mort = A(2,:);
% 
% dlmwrite('data_hosp.txt',hosp);
% dlmwrite('data_mort.txt',mort);
% 
% %% afficher les données hosp et mort
% jour = 1:64;
% A = xlsread('data_projet_prog.xlsx')';
% A=A/11500000;
% figure
% plot(jour,A(1,:));
% hold on;
% plot(jour,A(2,:));
%% affichage oscillateur
M=dlmread('integration.txt');
t=0:0.01:19.98; % à changer si nécessaire
for i=1:length(t)
    sol_exacte_y1(i) = cos(t(i));
end
figure 
plot(t,M(1,:),'*');
hold on
plot(t,sol_exacte_y1);

%figure
%semilogy(t,err1,'b');

% %% Affichage SIRQD
% 
% M=dlmread('integration.txt');
% t=0:0.01:63.99; % à changer si nécessaire
% 
% 
% figure 
% plot(t,M(1,:));
% hold on;
% plot(t,M(2,:));
% plot(t,M(3,:));
% plot(t,M(4,:));
% plot(t,M(5,:));
% legend('S','I','R','Q','D');
% 
% %% comparaison data et simu
% 
% A = xlsread('data_projet_prog.xlsx')';
% A=A/11500000;
% M=dlmread('integration.txt');
% jour = 1:64;
% t=0:0.01:63.99;
% 
% figure
% plot(t,M(4,:));
% hold on;
% plot(jour,A(1,:));
% legend('simu','data');
% title('comparaison données et résultat simulation : Hospitalisations');
% xlabel('t : 1 jour = 1 unité');
% ylabel('proportion de la population');
% 
% figure
% plot(t,M(5,:));
% hold on;
% plot(jour,A(2,:));
% legend('simu','data');
% title('comparaison données et résultat simulation : Mort');
% xlabel('t : 1 jour = 1 unité');
% ylabel('proportion de la population');
% 
% 
% for i=1:64
%    hosp(i) = M(4,i*100);  
% end
% err1=abs(hosp - A(1,:));
% for i=1:64
%    mort(i) = M(5,i*100);  
% end
% err2=abs(mort - A(2,:));
% 
% figure
% semilogy(jour,err1);
% hold on;
% semilogy(jour,err2);
% legend('hosp','mort');
% title('erreur absolue sur les données et résultat simulation : Mort');
% xlabel('jour');
% ylabel('erreur absolue');
% 
% %% simulation
% 
% A = xlsread('data_projet_prog.xlsx')';
% 
% M=dlmread('integration.txt');
% M=M*11500000;
% jour = 1:64;
% t=0:0.01:63.99;
% 
% figure
% plot(t,M(4,:));
% hold on;
% plot(jour,A(1,:));
% legend('simu','data');
% title('Comparaison données et résultat simulation déconfinement le 18 avril : Hospitalisations');
% xlabel('t : 1 jour = 1 unité');
% ylabel('Population');
% 
% figure
% plot(t,M(5,:));
% hold on;
% plot(jour,A(2,:));
% legend('simu','data');
% title('Comparaison données et résultat simulation déconfinement le 18 avril : Mort');
% xlabel('t : 1 jour = 1 unité');
% ylabel('Population');
% 
% 
% 
