let currentScene = null;

window.addEventListener("DOMContentLoaded", () => {
  fetch("http://localhost:3000/scene")
    .then(res => res.json())
    .then(data => {
      currentScene = data;
      displayScene();
    })
    .catch(err => console.error("Error loading initial scene:", err));
});

async function sendInput(input) {
  try {
    const response = await fetch('http://localhost:3000/run', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ input })
    });

    if (!response.ok) throw new Error("Failed to fetch from C backend");
    const data = await response.json();
    if (data.error) {
      alert(data.error);
      return;
    }
    if (data.history) {
      displayHistory(data.history);
    } else {
      currentScene = data;
      displayScene();
    }
    if (data.restart) {
      alert("The story has restarted!");
      currentScene = data;
      displayScene();
      return;
    }

    
    
  } catch (err) {
    console.error(err);
  }
}

function displayHistory(history) {
  const story = document.getElementById('story');
  const img = document.getElementById('ii');

  story.innerHTML = history.map(h => `<p>${h.description}</p>`).join("<hr>");
  img.src = '/images/' + history[history.length - 1].img; 
}

function displayScene() {
  const story = document.getElementById('story');
  const img = document.getElementById('ii');

  story.textContent = currentScene.description;
  img.src = '/images/' + currentScene.img;
}


document.getElementById('choice1').onclick = () => sendInput('1');
document.getElementById('choice2').onclick = () => sendInput('2');
document.getElementById('choice3').onclick = () => sendInput('3');
document.getElementById('undo').onclick = () => sendInput('U');
document.getElementById('redo').onclick = () => sendInput('R');
document.getElementById('save').onclick = () => sendInput('S');
document.getElementById('goto').onclick = () => sendInput('G');
document.getElementById('display').onclick = () => sendInput('D');
document.getElementById('exit').onclick = () => sendInput('E');