
#IFS=$'\n' read -d '' -r -a lines </home/ukoc/mangrove/phase2/lstm/data/java/CWE89OwaspCategories.txt
IFS=$'\n' read -d '' -r -a lines <Benchmark_v1.1_Scorecard_for_FBwFindSecBugs.csv

for i in "${lines[@]}"; do
	IFS=$',' read -d '' -r -a ADDR <<< "$i"
	benchNo="${ADDR[0]:13}"
	reportFileName=reports_owasp2/$benchNo"${ADDR[2]:0:1}${ADDR[3]:0:1}".xml

	if [ -f "$reportFileName" ]
	then
		echo "Report $reportFileName already exist."
	else
		classFileName=org.owasp.benchmark.testcode.BenchmarkTest$benchNo
		echo $classFileName
		sed 's/FILENAME/BenchmarkTest'$benchNo'/g' include_template_owasp.xml > include.xml
		./findsecbugs.sh -low -onlyAnalyze $classFileName -output $reportFileName -xml benchmark.jar
		python parseReport.py $reportFileName
	fi
done
