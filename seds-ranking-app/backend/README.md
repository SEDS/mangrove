# Ranking Service Backend

## General Information

This repository is the Blueprint server for the SEDS Ranking application. Once running, this application will be able to receive files from the frontend (located [here](https://github.iu.edu/semfulle/ranking-service-frontend)), and the server will process those files and run the SEDS Ranking python script on them. Then the results from the python script will be sent back to the frontend to be displayed.

## Running the Application

Here are the steps to run this repository.

1. Clone the SEDS Ranking python repo right outside this backend repo
2. Go through the Tutorial.pdf file that is located inside the python repo. Make sure you install everything that the tutorial says to install.
3. Test to make sure the SEDS Ranking python script works properly
    1. Download the Juliet test suite for C/C++ from [here](https://samate.nist.gov/SARD/testsuite.php)
    2. In the Juliet test suite search for the following file: `CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_33.cpp` and put it right inside the python repo directory
    3. Run this command from inside the python repo directory: `python main.py --weakness=CWE134 --SCATool=FlawFinder --sourceCode=./CWE134_Uncontrolled_Format_String__char_connect_socket_fprintf_33.cpp`
    4. If no errors, continue with the setup process
4. Back inside this repo (the backend repo), run `npm install`
5. Run the app with `node ./app`
6. The development server will be running on `localhost:5000`

## Structure

The structure of this application is quite simple. Below are some details...

### Routers
Within the **routers** folder, there is a single folder called **api**. This is where all of the routers that compose the server's api are stored. Within the api folder, there is just one file, [upload.js](app/routers/api/upload.js). This file is the router for the `uploads` endpoint. (*Note: The router file is "upload" and the actual endpoint is "uploads" with an extra 's'.*) This endpoint also takes in a query parameter which has a key called `weakness`. So, the complete endpoint url looks as follows: `http://localhost:5000/uploads/:weakness`.

### Controllers
Within the **controllers** folder, there is a single file called [upload.js](app/controllers/upload.js). This is where the logic for the upload route is stored. The controller defines a `SingleFileUploadAction` which allows the controller to handle file uploads. When a file is uploaded, it is stored in a `./temp` folder. Inside the `SingleFileUploadAction`, the file that was uploaded is run through the SEDS Ranking python script. The result of the python script are then gathered, formatted, and sent back to the frontend for display.

## TO DO

Currently, the backend application is using [this](app/services/fileProcessorMock.js) mock service to process the files that the backend receives from the frontend. This is because during the development of this application, the SEDS Ranking python script did not work properly. Whenever the python script is working, below are the steps that need to be completed in order for this project to work as expected.
- The application needs to be switched to using the [`fileProcessor.js`](app/services/fileProcessor.js) service instead of the `fileProcessorMock.js` service.
- When using this real service (assuming the python script is working properly), the results, after running the python script, should be stored in an xml file. The parsing of this file will need to be updated and revised in order to properly parse the non-mock xml file. This will be done in the `parseResults(xmlPath, weakness)` method found in the [upload controller](app/controllers/upload.js).
- Depending on what type of information that is stored in the xml file, you may also need to update the way the information is sent to the frontend which is also found in the [upload controller](app/controllers/upload.js).
- Depending on what type of information is stored in the xml file, you may also need to update the way the frontend displays the information. 
- It is unclear what type of weaknesses FlawFinder and CppCheck are able to look for. In the `util.js` file, the configured weakness types may need to change.
