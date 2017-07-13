set(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test_bin)

addtest(model_hash_provider_test model_hash_provider_test.cpp)
target_link_libraries(model_hash_provider_test
    model
    optional
    hash
    )

addtest(model_crypto_provider_test model_crypto_provider_test.cpp)
target_link_libraries(model_crypto_provider_test
    model
    hash
    crypto
)

addtest(model_commands_test model_commands.cpp)
target_link_libraries(model_commands_test
        model
        hash
        crypto
        schema
        )