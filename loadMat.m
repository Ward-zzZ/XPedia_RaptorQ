function [ cmData ] = loadMat(varargin)
%  [ cmData ] = loadMat(strBinFile, [],offset)
    
    strBinFile = varargin{1};  offset = 0; vecSHP = [];
    if 2 <= nargin,  vecSHP = varargin{2};  end
    if 3 <= nargin,  offset = varargin{3};  end


    
    fp = fopen(strBinFile,'rb');
    

    fseek(fp,0,'eof');     fileBytes = ftell(fp); Mlen = fileBytes/(4)-offset;
    dims = size(vecSHP,2);   CHKlen = 1; for jjj = 1 : dims, CHKlen *= vecSHP(jjj);  end
    Rlen = Mlen;  rSHP = [1 Rlen]; 
    if 0 < dims, Rlen = min(Rlen, CHKlen);   rSHP = vecSHP;  end

    fseek(fp,offset*4,'bof');     xx = fread(fp, [1 Rlen], 'float32');
     
    fclose(fp);
    cmData = xx;

    %dims = size(vecSHP,2);   CHKlen = 1; for jjj = 1 : dims, CHKlen *= vecSHP(jjj);  end


    cmData = reshape(cmData,rSHP);

end
