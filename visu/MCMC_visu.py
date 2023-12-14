


def quantiles_to_plot(x,quantiles,classe,compartiment,axes_subplot,title_plot):
    inf = quantiles[classe][compartiment].iloc[0]
    median = quantiles[classe][compartiment].iloc[1]
    sup = quantiles[classe][compartiment].iloc[2]

    axes_subplot.fill_between(x, inf, sup, alpha=.5, linewidth=0)
    axes_subplot.plot(x, median, linewidth=2)

    axes_subplot.title.set_text(title_plot)

    return



def quantiles_to_plot_calibration(x,quantiles,classe,compartiment,axes_subplot,title_plot,data_calibration,R,inf_R,sup_R):
    inf = quantiles[classe][compartiment].iloc[0]
    median = quantiles[classe][compartiment].iloc[1]
    sup = quantiles[classe][compartiment].iloc[2]

    axes_subplot.fill_between(x, inf, sup, alpha=.5, linewidth=0)
    axes_subplot.plot(x, median, linewidth=2)
    
    
    if(R == 0):
        axes_subplot.scatter(range(len(data_calibration)),data_calibration,marker = '*')
    elif(R == 1):
        axes_subplot.scatter(38, inf_R*17282163, marker='*')
        axes_subplot.scatter(38, sup_R*17282163, marker='*')


    axes_subplot.title.set_text(title_plot)

    return