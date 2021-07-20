%%% eSCENA_UmaM10_57Cell_PGs.bin_Mat11400x57  :   Propagation gain(dB) from each user to 57 sectors(size: 14400*57) 

%%% eSCENA_UmaM10_19Site_2Ds.bin_Mat11400x19  :   2D distance (meter) from each user  to 19 sites  (size: 14400*19) 
%%% eSCENA_UmaM10_57Cell_AGs.bin_Mat11400x57  :   Antenna gain (dB)   from each user  to 57 sectors(size: 14400*57) 
%%% eSCENA_UmaM10_19Site_los.bin_Mat11400x19  :   los identifier  for each of 11400*19 links       (size: 14400*19)
%%% eSCENA_UmaM10_19Site_PLs.bin_Mat11400x19  :   path loss  (dB)     from each user  to 19 sites  (size: 14400*19)
%%% eSCENA_UmaM10_19Site_SFs.bin_Mat11400x19  :   shadowing  (dB) for each user w.r.t each site    (size: 14400*19)  
%%% eSCENA_UmaM10_XYs_19Site.bin_CxM11400x19  :   XY position     for each user w.r.t each site    (size: 14400*19)

%%% eSCENA_UmaM10_SCell_2Ds.bin_Mat1x11400    :   2D distance (meter) from each user to serving cell (size: 1*14400)  
%%% eSCENA_UmaM10_SCell_AGs.bin_Mat1x11400    :   Antenna gain (dB)   from each user to serving cell (size: 1*14400)   
%%% eSCENA_UmaM10_SCell_SFs.bin_Mat1x11400    :   shadowing  (dB)  for  each user w.r.t serving cell (size: 1*14400)   
%%% eSCENA_UmaM10_SCell_PLs.bin_Mat1x11400    :   path loss  (dB)     from each user to serving cell (size: 1*14400)  
%%% eSCENA_UmaM10_SCell_hUT.bin_Mat1x11400    :   height (meter) of each user                        (size: 1*14400)             
%%% eSCENA_UmaM10_SCell_LOS.bin_Mat1x11400    :   los identifier  for each user in serving cell      (size: 1*14400) 
%%% eSCENA_UmaM10_SCell_O2I.bin_Imat1x11400   :   O2I identifier  for each user in serving cell      (size: 1*14400)  


% *****************************************************************************************************************************
% **   coupling_loss = antenn_gain + shadowing - path_loss, CDF of coupling loss for serving cell (calibraion phase1 in TR36.873)
% *****************************************************************************************************************************
SCell_CLsrc = {
'b.-', 'eSCENA_UmiM1_SCell_AGs.bin_Mat1x11400' ,  'eSCENA_UmiM1_SCell_SFs.bin_Mat1x11400',    'eSCENA_UmiM1_SCell_PLs.bin_Mat1x11400',
'r.-', 'eSCENA_UmiM10_SCell_AGs.bin_Mat1x11400' , 'eSCENA_UmiM10_SCell_SFs.bin_Mat1x11400',   'eSCENA_UmiM10_SCell_PLs.bin_Mat1x11400',
'k.-', 'eSCENA_UmaM1_SCell_AGs.bin_Mat1x11400' ,  'eSCENA_UmaM1_SCell_SFs.bin_Mat1x11400',    'eSCENA_UmaM1_SCell_PLs.bin_Mat1x11400',
'm.-', 'eSCENA_UmaM10_SCell_AGs.bin_Mat1x11400' , 'eSCENA_UmaM10_SCell_SFs.bin_Mat1x11400',   'eSCENA_UmaM10_SCell_PLs.bin_Mat1x11400'
};
figure(); 
for jjj = 1:4 ,   
    AGs = loadMat(SCell_CLsrc{jjj,2});  
    SFs = loadMat(SCell_CLsrc{jjj,3});  
    PLs = loadMat(SCell_CLsrc{jjj,4});  
    CLs = AGs + SFs - PLs;               % coupling_loss = antenn_gain + shadowing - path_loss
    cdf_CL = calcCDF(CLs,-160,-40);      % CDF of coupling loss samples
    plotCDF(cdf_CL,SCell_CLsrc{jjj,1});  
end  
xlabel('Coupling Loss(dB)'); title('Coupling Loss CDFs: blue: Umi@M=1, red: Umi@M=10, black: Uma@M=1, magenta: Uma@M=10');    grid minor;


% *****************************************************************************************************************************
% **     CDF of geometry  (calibraion phase1 in TR36.873)
% *****************************************************************************************************************************
figure(); 
sirCDFlist = { 
'b.-', 'eSCENA_UmiM1_CDF_sirs.bin_CxM1x400', 
'r.-', 'eSCENA_UmiM10_CDF_sirs.bin_CxM1x400',
'k.-', 'eSCENA_UmaM1_CDF_sirs.bin_CxM1x400', 
'm.-', 'eSCENA_UmaM10_CDF_sirs.bin_CxM1x400'
};

for jjj = 1:4 ,   cdfSIRs = loadCxM(sirCDFlist{jjj,2});  plotCDF(cdfSIRs,sirCDFlist{jjj,1});     end  
xlabel('sir(dB)'); title('sir CDFs: blue: Umi@M=1, red: Umi@M=10, black: Uma@M=1, magenta: Uma@M=10');    grid minor;

% *****************************************************************************************************************************


% *****************************************************************************************************************************
% **     CDF of los ZoD  (calibraion phase1 in TR36.873)
% *****************************************************************************************************************************
figure(); 
eodCDFlist = { 
'b.-', 'eSCENA_UmiM1_CDF_EOD.bin_CxM1x400', 
'r.-', 'eSCENA_UmiM10_CDF_EOD.bin_CxM1x400',
'k.-', 'eSCENA_UmaM1_CDF_EOD.bin_CxM1x400', 
'm.-', 'eSCENA_UmaM10_CDF_EOD.bin_CxM1x400'
};

for jjj = 1:4 ,   cdfSIRs = loadCxM(eodCDFlist{jjj,2});  plotCDF(cdfSIRs,eodCDFlist{jjj,1});     end  
xlabel('los ZoD(degree)'); title('los ZoD CDFs: blue: Umi@M=1, red: Umi@M=10, black: Uma@M=1, magenta: Uma@M=10'); xlim([70 120]);   grid minor;

% *****************************************************************************************************************************
eSCENA_UmaM1_LOAD50_TX10MHz_Alpha60_oneUser_SNRs.bin_Mat1x284989
% *****************************************************************************************************************************
% **     CDF of los ComP & Base  (using results form calibraion phase1 in TR36.873)
% *****************************************************************************************************************************
figure();  SNRrng = 50;
compCDFlist = { 
'g.-', 'eSCENA_UmaM1_LOAD50_TX10MHz_Alpha60_oneUser_SNRs.bin_Mat1x284989', 
'r.-', 'eSCENA_UmaM1_LOAD50_TX10MHz_Alpha60_ulBase_SINRs.bin_Mat1x284989', 
'b.-', 'eSCENA_UmaM1_LOAD50_TX10MHz_Alpha60_ulCoMP_SINRs.bin_Mat1x284989',
};



strScena = 'Uma'; TxMHz = 1;  SampN = 284989; M=1;   SNRrng = 80;  strMark=''
%eSCENA_UmaM10_LOAD50_TX10MHz_Alpha60_oneCoMP_SNRs.bin_Mat1x284989
strCFGpre  = strcat('eSCENA_',strScena,'M',int2str(M),'_LOAD50_TX',int2str(TxMHz),'MHz_Alpha60_')
strCFGpost = strcat('.bin_Mat1x' , int2str(SampN))
strTitle   = strcat(strScena,'M',int2str(M), strMark, ', load=50%, UETx@',int2str(M),'MHz, PwrCtrlAlpha=60%' ) 
compCDFlist = { 
'k.-', strcat(strCFGpre, 'oneCoMP_SNRs',strCFGpost), 
'g.-', strcat(strCFGpre, 'oneUser_SNRs',strCFGpost), 
'r.-', strcat(strCFGpre, 'ulBase_SINRs',strCFGpost), 
'b.-', strcat(strCFGpre, 'ulComB_SINRs',strCFGpost), 
'm.-', strcat(strCFGpre, 'ulJSMP_SINRs',strCFGpost), 
};
figure(1); title(strTitle)
figure(2); title(strTitle)


jjj=1; xx1=10*log10(loadMat(compCDFlist{jjj,2}));  myCDF(xx1,-SNRrng,SNRrng,compCDFlist{jjj,1});
jjj=2; xx2=10*log10(loadMat(compCDFlist{jjj,2}));  myCDF(xx2,-SNRrng,SNRrng,compCDFlist{jjj,1});
jjj=3; xx3=10*log10(loadMat(compCDFlist{jjj,2}));  myCDF(xx3,-SNRrng,SNRrng,compCDFlist{jjj,1});
jjj=4; xx4=10*log10(loadMat(compCDFlist{jjj,2}));  myCDF(xx4,-SNRrng,SNRrng,compCDFlist{jjj,1});
jjj=5; xx5=10*log10(loadMat(compCDFlist{jjj,2}));  myCDF(xx5,-SNRrng,SNRrng,compCDFlist{jjj,1});




strlist ={
['Black   : One UE,   max-ratio combining on 57 cells '],
['Green   : One UE,   receive on serving cell'],
['Red     : 50% Load, receive on serving cell'],
['Blue    : 50% Load, max-ratio combining on 57 cells '],
['Magenta : 50% Load, MRC & adv-rx on 57 cells'   ] }

dim = [0.15 0.6 0.6 0.6];
annotation('textbox',dim,'String',strlist);
