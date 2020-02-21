# 动态生成运行时配置文件

# 根据环境变量替换global_config.json中的默认值
if [ "${DB_HOST}" ];then
  sed -i "s/\"db_host\".*/\"db_host\": \"${DB_HOST}\",/" ./global_config.json
  echo "db_host ${DB_HOST}"
fi

if [ "${DB_PORT}" ];then
  sed -i "s/\"db_port\".*/\"db_port\": ${DB_PORT},/" ./global_config.json
  echo "db_port ${DB_PORT}"
fi


if [ "${REDIS_HOST}" ];then
  sed -i "s/\"redis_host\".*/\"redis_host\": \"${REDIS_HOST}\",/" ./global_config.json
  echo "redis_host ${REDIS_HOST}"
fi

if [ "${REDIS_PORT}" ];then
  sed -i "s/\"redis_port\".*/\"redis_port\": ${REDIS_PORT},/" ./global_config.json
  echo "redis_port ${REDIS_PORT}"
fi


if [ "${AES_KEY}" ];then
  sed -i "s/\"aes_key\".*/\"aes_key\": \"${AES_KEY}\",/" ./global_config.json
  echo "aes_key ${AES_KEY}"
fi

if [ "${AES_IV}" ];then
  sed -i "s/\"aes_iv\".*/\"aes_iv\": \"${AES_IV}\",/" ./global_config.json
  echo "aes_iv ${AES_IV}"
fi
