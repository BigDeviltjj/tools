set -eux
cur_file=`pwd`
for file in $(find ./ -name "*.sh")
do
  if [ ! "${file}" == "./install_all.sh" ]
  then
    cd ${cur_file}
    ${file}
  fi
done

