
IFS=$'\n' read -d '' -r -a lines </home/ukoc/mangrove/phase2/lstm/data/java/CWE89JulietStatsBalanced.txt
for i in "${lines[@]}"; do
	IFS=$',' read -d '' -r -a ADDR <<< "$i"
	fileName="${ADDR[0]:4}"
	subfolder="${ADDR[0]:2:1}"
	reportFileName=reports_juliet/s0$subfolder/"${fileName%.*}${ADDR[3]:0:1}"P.xml

	if [ -f "$reportFileName" ]
	then
		echo "Report $reportFileName already exist."
	else
		classFileName=testcases.CWE89_SQL_Injection.s0$subfolder.${fileName%.*}
		echo $classFileName
		sed 's/FILENAME/s0'$subfolder.${fileName%.*}'/g' include_template_juliet.xml > include.xml
		./findsecbugs.sh -low -onlyAnalyze $classFileName -output $reportFileName -xml CWE89_SQL_Injection_s0$subfolder.jar
		python parseReport.py $reportFileName
	fi
	#exit
done
