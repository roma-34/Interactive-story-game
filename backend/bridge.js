const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');
const readline = require('readline');

const app = express();
app.use(cors());
app.use(express.json());


app.use('/images', express.static(path.join(__dirname, 'images')));


const exePath = path.join(__dirname, 'anthea.exe');
const child = spawn(exePath, [], { stdio: ['pipe', 'pipe', 'pipe'] });

child.stderr.on('data', data => console.error('C error:', data.toString()));

const rl = readline.createInterface({ input: child.stdout });

let latest = null;


rl.on('line', line => {
  latest = line;
  
});


function sendCommand(cmd) {
  return new Promise((resolve, reject) => {
    let done = false;

    const onLine = (line) => {
      if (done) return;
      done = true;
      rl.removeListener('line', onLine);
      resolve(line);
    };
 
    rl.on('line', onLine);

    child.stdin.write(cmd + '\n');

    setTimeout(() => {
      if (!done) {
        rl.removeListener('line', onLine);
        reject('Timeout');
      }
    }, 3000);
  });
}


app.get('/scene', (req, res) => {
  if (!latest) return res.status(500).send('No scene yet.');
  try {
    res.json(JSON.parse(latest));
  } catch (err) {
    console.error('JSON parse error:', latest);
    res.status(500).send('Invalid C output');
  }
});


app.post('/run', async (req, res) => {
  try {
    const input = req.body.input || "";
    const line = await sendCommand(input);
    latest = line;
    const data = JSON.parse(line)
    if (data.restart) {
      console.log("Story restarted!");
      res.json({ restart: true, description: data.description, img: data.img });
      return;
    }
    res.json(data);
  } catch (err) {
    console.error(err);
    res.status(500).send('Error running C command');
  }
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
