file(GLOB_RECURSE OPERATOR_C_FILES *.c)

target_sources(
  ${ONNC_RUNTIME_LIB_NAME}
  PRIVATE ${OPERATOR_C_FILES}
)
