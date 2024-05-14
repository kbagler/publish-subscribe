# Code coverage is available in Debug build only because code coverage requires
# no compile optimization
add_compile_options(
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-fprofile-arcs>
    $<$<CONFIG:DEBUG>:-ftest-coverage>
)
add_link_options(
    $<$<CONFIG:DEBUG>:-coverage>
)

