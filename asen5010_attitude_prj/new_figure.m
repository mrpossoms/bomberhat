function [ fig ] = new_figure()
%NEW_FIGURE creates the next available figure.

fig = figure(length(findobj('type', 'figure')) + 1);

end

