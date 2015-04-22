function [rsq] = Linearfit( PLACG,PLAD )
p = polyfit(PLACG,PLAD,1);
PLAfit=polyval(p,PLACG);
PLAresid = PLAD - PLAfit;
SSresid = sum(PLAresid.^2);
SStotal = (length(PLAD)-1) * var(PLAD);
rsq = 1 - SSresid/SStotal;
end

