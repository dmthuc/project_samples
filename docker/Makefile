image:
	docker build --network=host -t minhthucdao1/test .
test:
	docker run --rm -it minhthucdao1/test /bin/sh
run:
	docker run --rm -it minhthucdao1/test /dao_wp/run.sh
push:
	docker push minhthucdao1/test
test_volume1:
	docker run --rm -it --mount 'type=volume,src=vol1,dst=/vol_path1/' minhthucdao1/test /bin/sh
test_volume2:
	docker run --rm -it --mount 'type=volume,src=vol1,dst=/vol_path/' minhthucdao1/test /bin/sh
