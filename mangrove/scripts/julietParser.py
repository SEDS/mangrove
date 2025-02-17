#!/usr/bin/env python

import cPickle, re, os, string, random
from os.path import isfile, join

def get_immediate_subdirectories(a_dir):
	return [name for name in os.listdir(a_dir) if os.path.isdir(os.path.join(a_dir, name))]

def obfuscate(sample):
	randStr=''.join(random.choice(string.ascii_lowercase) for _ in xrange(3))
	sample = re.sub('\s+', ' ', sample) # remove multi spaces
	sample = re.sub('good', randStr, sample) #remove the word good 
	sample = re.sub('bad', randStr, sample) #remove the word bad
	sample = re.sub('/\*[^;/]* \*/', '', sample) #remove most of the comments old pattern /\*[\w*:,\(\)-*\d\s_]* \*/
	sample = re.sub('\"[\w+,\(\)\s]+\"', '" STRING "', sample) #unify print out strings
	return sample.strip()

def tokenize(sample):
	helpDict={'\"':' " ', '\(':' ( ', '\)': ' ) ','\[':' [ ','\]': ' ] ','\{': ' { ', '\'':' \' ', ';':' ; ', '==':' == ', '<':' < ', '>':' > ', 
	'!':' ! ', '\+\+':' ++ ', '--':' -- ', '\+': ' + ', '-':' - ', '\#':' # ', '\*':' * ', ',':' , ', '\!=':' != ', '&':' & ', '=':' = '} # '':'  '
	for key in helpDict:
		sample = re.sub(key, helpDict[key], sample)
	sample = re.sub('=\s=','==', sample)
	sample = re.sub('>\s>','>>', sample)
	sample = re.sub('<\s<','<<', sample)
	sample = re.sub('/\s\*','/*', sample)
	sample = re.sub('\*\s/','*/', sample)
	sample = re.sub(' \d+ ',' N ', sample)
	return sample.strip()

def processSample(cweNumber, sampleClass, omitStr, lines):
	macroPattern = re.compile("#(if.*def|endif)")
	sample=''
	isSampleLine=False
	for line in lines: 
		if '/* '+omitStr+' */' in line:
			break
		elif omitStr in line:
			isSampleLine = not isSampleLine
		elif isSampleLine and not macroPattern.match(line):
			sample+=line.rstrip()+' '
	if sample is not '': print obfuscate(tokenize(sample)) + ' ' + cweNumber + ' ' + sampleClass + 'positive'

def processFile(fileName):
	cweNumber=fileName[fileName.rfind('/')+1::]
	cweNumber=cweNumber[0:cweNumber.index('_')]
	with open(fileName) as file: lines = file.readlines()
	processSample(cweNumber, 'bad', 'OMITBAD', lines)
	processSample(cweNumber, 'good', 'OMITGOOD', lines)

def processJulietTestCases(julietDir, CWEs):
	pattern = re.compile("CWE\d{2,3}.*\.(c|cpp)")
	files = []
	for cwe in CWEs:
		directory=julietDir + cwe
		if not os.path.isdir(directory + '/s01/'):
			files += [join(directory, f) for f in os.listdir(directory) if (isfile(join(directory, f)) and pattern.match(f))]
		else:
			subDirs=get_immediate_subdirectories(directory)
			for s in subDirs:
				subDir=directory+'/'+s
				files += [join(subDir, f) for f in os.listdir(subDir) if (isfile(join(subDir, f)) and pattern.match(f))]
	for fileName in files: 
		processFile(fileName) 
		#break

if __name__ == '__main__':
	julietDir = '/Users/ukoc/sa-lstm/juliet/testcases/'
	CWEs = ['CWE114_Process_Control', 'CWE121_Stack_Based_Buffer_Overflow', 'CWE122_Heap_Based_Buffer_Overflow', 'CWE123_Write_What_Where_Condition', 'CWE124_Buffer_Underwrite', 'CWE126_Buffer_Overread', 'CWE127_Buffer_Underread', 'CWE134_Uncontrolled_Format_String', 'CWE15_External_Control_of_System_or_Configuration_Setting', 'CWE176_Improper_Handling_of_Unicode_Encoding', 'CWE188_Reliance_on_Data_Memory_Layout', 'CWE190_Integer_Overflow', 'CWE191_Integer_Underflow', 'CWE194_Unexpected_Sign_Extension', 'CWE195_Signed_to_Unsigned_Conversion_Error', 'CWE196_Unsigned_to_Signed_Conversion_Error', 'CWE197_Numeric_Truncation_Error', 'CWE222_Truncation_of_Security_Relevant_Information', 'CWE223_Omission_of_Security_Relevant_Information', 'CWE226_Sensitive_Information_Uncleared_Before_Release', 'CWE23_Relative_Path_Traversal', 'CWE242_Use_of_Inherently_Dangerous_Function', 'CWE244_Heap_Inspection', 'CWE247_Reliance_on_DNS_Lookups_in_Security_Decision', 'CWE252_Unchecked_Return_Value', 'CWE253_Incorrect_Check_of_Function_Return_Value', 'CWE256_Plaintext_Storage_of_Password', 'CWE259_Hard_Coded_Password', 'CWE272_Least_Privilege_Violation', 'CWE273_Improper_Check_for_Dropped_Privileges', 'CWE284_Improper_Access_Control', 'CWE319_Cleartext_Tx_Sensitive_Info', 'CWE321_Hard_Coded_Cryptographic_Key', 'CWE325_Missing_Required_Cryptographic_Step', 'CWE327_Use_Broken_Crypto', 'CWE328_Reversible_One_Way_Hash', 'CWE338_Weak_PRNG', 'CWE36_Absolute_Path_Traversal', 'CWE364_Signal_Handler_Race_Condition', 'CWE366_Race_Condition_Within_Thread', 'CWE367_TOC_TOU', 'CWE369_Divide_by_Zero', 'CWE377_Insecure_Temporary_File', 'CWE390_Error_Without_Action', 'CWE391_Unchecked_Error_Condition', 'CWE396_Catch_Generic_Exception', 'CWE397_Throw_Generic_Exception', 'CWE398_Poor_Code_Quality', 'CWE400_Resource_Exhaustion', 'CWE401_Memory_Leak', 'CWE404_Improper_Resource_Shutdown', 'CWE415_Double_Free', 'CWE416_Use_After_Free', 'CWE426_Untrusted_Search_Path', 'CWE427_Uncontrolled_Search_Path_Element', 'CWE440_Expected_Behavior_Violation', 'CWE457_Use_of_Uninitialized_Variable', 'CWE459_Incomplete_Cleanup', 'CWE464_Addition_of_Data_Structure_Sentinel', 'CWE467_Use_of_sizeof_on_Pointer_Type', 'CWE468_Incorrect_Pointer_Scaling', 'CWE469_Use_of_Pointer_Subtraction_to_Determine_Size', 'CWE475_Undefined_Behavior_for_Input_to_API', 'CWE476_NULL_Pointer_Dereference', 'CWE478_Missing_Default_Case_in_Switch', 'CWE479_Signal_Handler_Use_of_Non_Reentrant_Function', 'CWE480_Use_of_Incorrect_Operator', 'CWE481_Assigning_Instead_of_Comparing', 'CWE482_Comparing_Instead_of_Assigning', 'CWE483_Incorrect_Block_Delimitation', 'CWE484_Omitted_Break_Statement_in_Switch', 'CWE500_Public_Static_Field_Not_Final', 'CWE506_Embedded_Malicious_Code', 'CWE510_Trapdoor', 'CWE511_Logic_Time_Bomb', 'CWE526_Info_Exposure_Environment_Variables', 'CWE534_Info_Exposure_Debug_Log', 'CWE535_Info_Exposure_Shell_Error', 'CWE546_Suspicious_Comment', 'CWE561_Dead_Code', 'CWE562_Return_of_Stack_Variable_Address', 'CWE563_Unused_Variable', 'CWE570_Expression_Always_False', 'CWE571_Expression_Always_True', 'CWE587_Assignment_of_Fixed_Address_to_Pointer', 'CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer', 'CWE590_Free_Memory_Not_on_Heap', 'CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory', 'CWE605_Multiple_Binds_Same_Port', 'CWE606_Unchecked_Loop_Condition', 'CWE615_Info_Exposure_by_Comment', 'CWE617_Reachable_Assertion', 'CWE620_Unverified_Password_Change', 'CWE665_Improper_Initialization', 'CWE666_Operation_on_Resource_in_Wrong_Phase_of_Lifetime', 'CWE667_Improper_Locking', 'CWE672_Operation_on_Resource_After_Expiration_or_Release', 'CWE674_Uncontrolled_Recursion', 'CWE675_Duplicate_Operations_on_Resource', 'CWE676_Use_of_Potentially_Dangerous_Function', 'CWE680_Integer_Overflow_to_Buffer_Overflow', 'CWE681_Incorrect_Conversion_Between_Numeric_Types', 'CWE685_Function_Call_With_Incorrect_Number_of_Arguments', 'CWE688_Function_Call_With_Incorrect_Variable_or_Reference_as_Argument', 'CWE690_NULL_Deref_From_Return', 'CWE758_Undefined_Behavior', 'CWE761_Free_Pointer_Not_at_Start_of_Buffer', 'CWE762_Mismatched_Memory_Management_Routines', 'CWE773_Missing_Reference_to_Active_File_Descriptor_or_Handle', 'CWE775_Missing_Release_of_File_Descriptor_or_Handle', 'CWE78_OS_Command_Injection', 'CWE780_Use_of_RSA_Algorithm_Without_OAEP', 'CWE785_Path_Manipulation_Function_Without_Max_Sized_Buffer', 'CWE789_Uncontrolled_Mem_Alloc', 'CWE832_Unlock_of_Resource_That_is_Not_Locked', 'CWE835_Infinite_Loop', 'CWE843_Type_Confusion', 'CWE90_LDAP_Injection']
	processJulietTestCases(julietDir, CWEs)
