#!/usr/bin/python
from ROOT import TH2D
import sys

data=[]
fl=open (sys.argv[1])
h=TH2D  ("hist", "Histogram",1000,0,1/2.,1000,0,1/2.)
for line in fl:
  h.Fill (
  float(line.split()[int(sys.argv[2])]),
  float(line.split()[int(sys.argv[3])]))
h.Draw("colz")
h.GetXaxis().SetTitle (sys.argv[2])
h.GetYaxis().SetTitle (sys.argv[3])
raw_input()
