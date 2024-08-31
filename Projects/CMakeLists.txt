function(AddProject projectName)
    add_subdirectory(${projectName})
    set_target_properties(${projectName} PROPERTIES FOLDER Projects)
endfunction()

AddProject(Breakout)
AddProject(Sandbox)

# add_subdirectory(Breakout)
# set_target_properties(Breakout PROPERTIES FOLDER Projects)
#
# add_subdirectory(SandBox)
# set_target_properties(SandBox PROPERTIES FOLDER Projects)