FLAW_FINDER_CWES = [ 126, 134 ];
CPP_CHECK_CWES = [ 401, 476, 762 ]


const determineSCATool = (weakness, tool) => {
  // determine what SCA tool supports the CWE weakness type
  if (!FLAW_FINDER_CWES.includes(weakness) && !CPP_CHECK_CWES.includes(weakness)) {
    throw Error('This CWE is not supported by any of the SCA tools we\'re using');
  }
  else {
    if (tool == "FlawFinder") {
      return "FlawFinder";
    }
    else if (tool === "CppCheck") {
      return "CppCheck";
    }
    else {
      throw Error('This CWE is not supported by any of the SCA tools we\'re using');
    }
  }
}

module.exports = { determineSCATool }