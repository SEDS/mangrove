
IFS=$'\n' read -d '' -r -a lines </home/ukoc/mangrove/phase2/lstm/data/java/CWE89OwaspCategories.txt
for i in "${lines[@]}"; do
	IFS=$',' read -d '' -r -a ADDR <<< "$i"
	benchNo="${ADDR[0]:13}"
	reportFileName=reports_owasp/$benchNo"${ADDR[1]:0:1}"P.xml

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
