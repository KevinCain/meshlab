# Meshlab Tools for Epigraphers

These tools are meant to help you render orthographic views of 3D models for archaeological publication by simplifying, segmenting, cleaning and rendering 3D meshes.

Before producing final plates for publication from 3D models, we find it useful to orient an orthographic camera view perpendicular to the plane of the model, and then set the the model’s rotation to absolute level.  The tools below are intended to do just that.  Because we often work with large meshes, our approach simplifies the model while you place it, then applies your transformations to the original model before rendering at full resolution.

INSIGHT has written several tools for Paolo Cignoni's [Meshlab] (http://sourceforge.net/p/meshlab/code/HEAD/tree/trunk/meshlab/src/) that we hope are useful to epigraphers creating plates for archaeological publications.

Our base Meshlab build is based on [Jerdak's Meshlab](https://github.com/Jerdak/meshlab) snapshot of Meshlab circa version 1.3.2.  [MeshLab](http://meshlab.sourceforge.net/) has not been updated since April 2 2014 (version 1.3.3), though CNR continues to use the library, update it to QT5, et cetera.  To quote Jerdak:  "The commit logs, as of 01 February 2016, indicate that version 1.4 is seeing active development but there has not been any official news."

For more on Jerdak's repository and his fine work, please see:  [Jerdak's Meshlab](https://github.com/Jerdak/meshlab)

### To compile MeshLab and all MeshLab plugins:

Download the INSIGHT Meshlab source to ~/meshlab with:
```
cd ~
git clone https://github.com/KevinCain/meshlab
```

Install OpenCV and QT’s make utility (if you don’t have it):
```
sudo apt-get install libqt4-dev
```

Compile the libraries Meshlab requires:
```
cd ~/meshlab/meshlab/src/external
qmake -recursive external.pro
make
```

Next, compile MeshLab and its plugins:
```
cd ~/meshlab/meshlab/src/
qmake -recursive meshlab_full.pro
make
```

CNR's Meshlab wiki is available here:
 http://sourceforge.net/p/meshlab/code/HEAD/tree/trunk/meshlab/src/
# meshlab
