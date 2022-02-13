function plotter3( x, y, z, ttitle )
%PLOTTER time and vector are vectors. The former have be multidimensional.
%The `labels` vector is for xlabel, ylabel, title in that order. The final
%argument, `legends`, is optional.

new_figure();
plot3(x, y, z)
if ~isempty(ttitle)
    title(ttitle)
end
end

