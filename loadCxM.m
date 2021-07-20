function [ cxmData ] = loadCxM(varargin)
%  [ cxmData ] = loadCxM(strBinFile, [],offset)
    
    strBinFile = varargin{1};  offset = 0; vecSHP = [];
    if 2 <= nargin,  vecSHP = varargin{2};  end
    if 3 <= nargin,  offset = varargin{3};  end

    
    fp = fopen(strBinFile,'rb');

    fseek(fp,0,'eof');     fileBytes = ftell(fp); Mlen = fileBytes/(4*2)-offset
    if(0 == size(vecSHP,1)),  vecSHP = [ 1  Mlen];  end

    dims = size(vecSHP,2);   CHKlen = 1; for jjj = 1 : dims, CHKlen *= vecSHP(jjj);  end

    Rlen = Mlen;  rSHP = [1 Rlen];       if 0 < dims,  Rlen = min(Rlen, CHKlen);   rSHP = vecSHP;  end

    fseek(fp,offset*4*2,'bof');     xx = fread(fp, [1 Rlen*2], 'float');

    fclose(fp);

    cxmData = xx(1:2:Rlen*2) + j*xx(2:2:Rlen*2);

    

    cxmData = reshape(cxmData,vecSHP);


end
