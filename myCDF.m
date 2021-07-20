function [ bins vfCDF ] = myCDF(vfData, fMIN, fMAX, strcolor)
    Vlen = size(vfData,2);   CDFlen=400;  vfPDF = zeros(1,CDFlen+1);
    fmin = min(vfData);
    fmax = max(vfData);
    fStep = CDFlen/(fMAX-fMIN);  bins = fMIN : (fMAX-fMIN)/CDFlen : fMAX;
    for jjj = 1 : Vlen,
        inow =  floor((vfData(jjj) - fMIN)*fStep + 0.5);
        vfPDF(inow) += 1;
    end
    fsum = 0;  fScale = 1.0/sum(vfPDF);  vfCDF = zeros(1,CDFlen+1);
    for jjj = 1:CDFlen+1, 
        fsum += vfPDF(jjj)*fScale;
        vfCDF(jjj) = fsum;

    end
    vfPDF0 = vfPDF./max(vfPDF)*0.5;
    %figure(); plot(bins,vfCDF,'b.-');    hold on;  plot(bins, vfPDF0,'r.--'); grid minor;  ylim([0 1.0]);
    figure(1);hold on; plot(bins,vfCDF,strcolor);   grid minor;  ylim([0 1.0]); 
    figure(2);hold on; plot(bins, vfPDF0,strcolor); grid minor;  ylim([0 1.0]);



end