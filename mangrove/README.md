# README #

This is the local mangrove project repository for UMD people. It is setup as a 
maven project ready to import into eclipse. Code preprocessing is mostly handled
in the java files under src directory. Machine learning and data analysis are hanlded
in the python and/or shell scripts that are under lstm and scripts directories.

### Publications

 * Koc, U., Saadatpanah, P., Foster, J. S., & Porter, A. A. (2017, June). _Learning a classifier for false positive error reports emitted by static code analysis tools._ In Proceedings of the 1st ACM SIGPLAN International Workshop on Machine Learning and Programming Languages (pp. 35-42). ACM.

For the case study in this publication, we used following components of this repository;
 
 - the slicig module under src
 - under lstm directory, preprocessCodeData.py is the script that prepares the data and lstm.py is the file that implements the lstm algorithm with several optimization algorithms 
 - data files under data/java
    - Used set of error reports; CWE89OwaspCategories.txt
    - Dictionaries; dictForSlicesOwasp.java, dictForByteCode.java (consumed by lstm.py)
    - Training sets; CWE89OwaspByteCode_Train.java, CWE89OwaspSlices_Train.java (consumed by lstm.py)
    - Validation sets; CWE89OwaspSlices_Valid.java, CWE89OwaspByteCode_Valid.java (consumed by lstm.py)
    - Two samples in Figure 4; CWE89OwaspSlices_2Sample.java (processed with script color_map.py)
  
#### Repeating the experiments
  
  * To reprocude the error reports, run 'findsecbugs_owasp.sh' under findsecbugs directory. Note that, 
  we augmented FindSecBugs jar file to include the bytecode of the method body into the error report.
    
  * Computing the slices, just run MyWarningSlicer.java in eclipse with no arguments.

  * Computing slice dataset from slices, run parseSlice.py under scripts directory, i.e. `./parseSlice.py`
  
  * Computing bytecode dataset from error reports, run `parseReports.py` under findsecbugs directory, i.e. `./parseReports.py`
  
  * To repeat the lstm training, run lstm.py script, i.e. `THEANO_FLAGS="floatX=float32" python lstm.py 4`. 
  It might be necessary to update the default values of `dataFile`, `reload_model`, and `saveto` 
  parameters acooring to you environment. Make sure that `dataFile` points to the training set and 
  line 48 of `preprocessCodeData.py` points to the correspoding dictionary file.  
  
  * After having a model trained just add the argument test to the command, i.e. `THEANO_FLAGS="floatX=float32" python lstm.py 4 test`
  and set the dataFile fo the validation file
  
  * To reprocude the Figure 4, just run the color_map.py script, i.e. `./color_map.py`. Note that this 
  script uses precoputed output values which are stored in `h_array.py` under scripts directory.

Note that, the paths are hardcoded in the most of the scripts mentioned above. They need to be updates 
according to the execution environments directory structure.

