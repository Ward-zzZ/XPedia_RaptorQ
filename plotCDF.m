function [  ] = plotCDF(varargin)
%  [  ] = plotCDF(strBinFile, [],offset)
    
    cxCDF = varargin{1};  strColor = 'r.-'; 
    if 2 <= nargin,  strColor = varargin{2};  end
    

    hold on; plot(real(cxCDF),imag(cxCDF),strColor); ylim([0 1.0]); 

end
