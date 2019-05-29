ssh-keygen -t rsa
echo "
Host tjj
HostName sgpu.jiamingsun.ml
User tangjiajie
" >> ~/.ssh/config

ssh tjj mkdir -p .ssh
cat ~/.ssh/id_rsa.pub | ssh tjj 'cat >> .ssh/authorized_keys'
ssh tjj "chmod 700 .ssh; chmod 640 .ssh/authorized_keys"


