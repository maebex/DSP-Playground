#!/usr/bin/python3

import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import simplejson as json
import getopt
import math



def loadData(fpath):
    try:
        f = open(fpath, 'r')
    except OSError:
        print("Could not open/read file: ", fpath)
        sys.exit()
    with  f:
        data = json.load(f)
    return data




def plotDecomposition(data, outpath):
    # Plot type ReImMagPha
    # All four graphs in one image
    # data contained in a dictionary: data
    # output file name and path specificed by: outpath
    fig, axs = plt.subplots(2, 2, figsize=(15, 12), constrained_layout=True)

    y = data["Payload"]["Rectangular"]["Real"]
    n = len(y)
    x = np.linspace(0,n-1,n)  
    axs[0,1].plot(x,
                  y, 
                  marker='o', 
                  #linestyle = 'None'
                  )
    minimum = math.floor(min(y))*1.1
    maximum = math.ceil(max(y))*1.1
    if minimum == maximum:
        if minimum == 0:
            minimum = -1.
            maximum = 1.
        else:
            minimum *= 0.8
            maximum *= 1.2
    axs[0,1].set_ylim(minimum, maximum)
    axs[0,1].set_xlabel('Frequency Component')
    axs[0,1].set_ylabel('Real part')
    axs[0,1].grid(True)

    y = data["Payload"]["Rectangular"]["Imaginary"]
    n = len(y)
    x = np.linspace(0,n-1,n)  
    axs[1,1].plot(x,
                  y, 
                  marker='o', 
                  #linestyle = 'None'
                  )
    minimum = math.floor(min(y))*1.1
    maximum = math.ceil(max(y))*1.1
    if minimum == maximum:
        if minimum == 0:
            minimum = -1.
            maximum = 1.
        else:
            minimum *= 0.8
            maximum *= 1.2
    axs[1,1].set_ylim(minimum, maximum)
    axs[1,1].set_xlabel('Frequency Component')
    axs[1,1].set_ylabel('Imaginary part')
    axs[1,1].grid(True)

    y = data["Payload"]["Polar"]["Magnitude"]
    n = len(y)
    x = np.linspace(0,n-1,n)  
    axs[0,0].plot(x,
                  y, 
                  marker='o', 
                  #linestyle = 'None'
                  )
    minimum = math.floor(min(y))*1.1
    maximum = math.ceil(max(y))*1.1
    if minimum == maximum:
        if minimum == 0:
            minimum = -1.
            maximum = 1.
        else:
            minimum *= 0.8
            maximum *= 1.2
    axs[0,0].set_ylim(minimum, maximum)
    axs[0,0].set_xlabel('Frequency Component')
    axs[0,0].set_ylabel('Magnitude')
    axs[0,0].grid(True)

    y = data["Payload"]["Polar"]["Phase"]
    n = len(y)
    x = np.linspace(0,n-1,n)
    y_ticks = np.linspace(-180, 180, 9)
    axs[1,0].plot(x,
                  y, 
                  marker='o', 
                  #linestyle = 'None'
                  )
    minimum = min(y)*1.1
    maximum = max(y)*1.1
    if minimum == maximum:
        if minimum == 0:
            minimum = -1.
            maximum = 1.
        else:
            minimum *= 0.8
            maximum *= 1.2
    axs[1,0].set_ylim(minimum, maximum)
    axs[1,0].set_xlabel('Frequency Component')
    axs[1,0].set_ylabel('Phase in rad')
    # axs[1,0].set_yticks(y_ticks)
    axs[1,0].grid(True)

    plt.savefig(outpath)

    return



def plotSignal(data, outpath):
    # Plot type ReImMagPha
    # data contained in a dictionary: data
    # output file name and path specificed by: outpath
    fig, axs = plt.subplots(2, 1, figsize=(15, 12), constrained_layout=True)

    y = data["SampleData"]
    n = len(y)
    x = np.linspace(0,n-1,n)  
    axs[0].plot(x,
                y, 
                marker='.', 
                #linestyle = 'None'
                )
    minimum = math.floor(min(y))*1.1
    maximum = math.ceil(max(y))*1.1
    axs[0].set_ylim(minimum, maximum)
    axs[0].set_xlabel('Sample nummber')
    axs[0].set_ylabel('Value')
    axs[0].grid(True)

    minimum = math.floor(min(y))
    maximum = math.ceil(max(y))
    width = maximum-minimum+1
    axs[1].hist(y, bins=width)
    axs[1].set_xlabel('Value')
    axs[1].set_ylabel('Occurences')
    axs[1].grid(True)

    plt.savefig(outpath)

    return


def main(argv):
    inputfile = ""
    outputfile = ""
    force = False
    opts, args = getopt.getopt(argv,"hi:o:f",["ifile=","ofile=", "force="])
    for opt, arg in opts:
        if opt == '-h':
            print ('./DSPPG_Plot.py -i <inputfile> -o <outputfile> -f (force output replacement)')
            sys.exit()
        elif opt in ("-i", "--ifile"):
            inputfile = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-f", "--force"):
            force = True


    print("---------------------------------------------------------------------------------")
    print("Input file: \t\t", inputfile)
    print("Output file: \t\t", outputfile)
    print("Force replacement: \t", force)
    print("---------------------------------------------------------------------------------")
    print("")

    isFile = os.path.isfile(inputfile)
    if isFile is False:
        print("Input file does not exist: ", inputfile)
        sys.exit()

    isFile = os.path.isfile(outputfile)
    if (isFile is True) and (force is False):
        print("Force is disabled and file does already exist: ", outputfile)
        sys.exit()

    data = loadData(inputfile)

    if data["PlotType"] == "Decomposition":
        plotDecomposition(data, outputfile)
    elif data["PlotType"] == "Signal":
        plotSignal(data, outputfile)
    else:
        print("Unrecognized option: ", data.plotType)

    return


if __name__ == "__main__":
    print("Python version:")
    print (sys.version)
    print("Version info:")
    print (sys.version_info)
    print("")
    print("")

    main(sys.argv[1:])
