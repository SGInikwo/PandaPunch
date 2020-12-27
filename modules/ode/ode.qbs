import qbs
Module {
    Depends { name: "cpp" }
    property string odePath: "/Users/goldy/Dev/_Libraries/ode"
    cpp.includePaths: odePath + "/include"
    cpp.libraryPaths: odePath + "/ode/src/.libs"
    cpp.staticLibraries: "ode"
}

