# Smoke tests verifying core library linkage and CLI startup.
# GoogleTest integration will be added here in Milestone 1 task 6.
add_executable(astra_smoke_test
    smoke_test.cpp
)

target_link_libraries(astra_smoke_test
    PRIVATE
        astra_core
        astra_warnings
)

add_test(NAME astra_core_smoke COMMAND astra_smoke_test)
add_test(NAME astra_cli_smoke COMMAND astra)

