import os

port = "NXT_PORT_S" + waitFor.Port
sign = waitFor.Sign
if sign == "меньше":
  sign = "<"
elif sign == "больше":
  sign = ">"
elif sign == "не меньше":
  sign = ">="
elif sign == "не больше":
  sign = "<="
elif sign == "равно":
  sign = "=="

condition = sign + " " + waitFor.Distance

waitForSonarCode = "while (!(ecrobot_get_sonar_sensor(" + port + ") " + condition + "))\n{}\n"
initCode = "ecrobot_init_sonar_sensor(" + port + ");\n"
terminateCode = "ecrobot_term_sonar_sensor(" + port + ");\n"

relPath = "nxt-tools/program0.c"
absPath = os.path.join(scriptDir, relPath)

codeFile = open(absPath, 'r')
code = codeFile.read()

if code.find(initCode) == -1:
  code = code.replace("@@INITHOOKS@@", initCode + "@@INITHOOKS@@")
  code = code.replace("@@TERMINATEHOOKS@@", terminateCode + "@@TERMINATEHOOKS@@")

code = code.replace("@@CODE@@", waitForSonarCode + "@@CODE@@")

codeFile.close()
codeFile = open(absPath, 'w')
codeFile.write(code)
codeFile.close()
