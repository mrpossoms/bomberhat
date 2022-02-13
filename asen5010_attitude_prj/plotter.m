function plotter( time, vector, labels, legends, cst, semlog )
%PLOTTER time and vector are vectors. The former have be multidimensional.
%The `labels` vector is for xlabel, ylabel, title in that order. The final
%argument, `legends`, is optional.

new_figure();
if nargin >= 6 && semlog
    semilogy(time, vector)
else
    plot(time, vector);
end

if ~isempty(labels)
    xlabel(labels(1))
    if length(labels) > 1
        ylabel(labels(2))
    end
    if length(labels) > 2
        title(labels(3))
    end
end

if nargin >= 4 && ~isempty(legends)
    legend(legends)
end

if nargin >= 5 && cst ~= 0
    hold on
    plot(time, ones(size(time)) * cst)
end

end

