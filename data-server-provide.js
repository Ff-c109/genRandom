const http = require("http");
const { spawn } = require("child_process");

const server = http.createServer((req, res) => {
	res.setHeader('Content-Type', 'text/plain');
	if(req.url == "/genRandom") {
		const rdGr = spawn("./genRand");
		rdGr.stdout.on('data', d => {
			res.write(d);
		});
		rdGr.on('exit', () => {
			res.end();
			console.log("close");
			server.close();
		});
	}
	else {
		res.end("Can't recongnize");
	}
});

server.listen(parseInt(process.env.PORT));

