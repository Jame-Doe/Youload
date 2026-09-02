async function sendLinkToServer(youtubeLink, format) {
  const btnDownload = document.querySelector('.btn-download');

  try {
    btnDownload.innerHTML = `<span>Processando...</span> <i class="fa-solid fa-spinner fa-spin"></i>`;
    btnDownload.disabled = true;

    const response = await fetch('/youtube_link', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({
        value: youtubeLink,
        format: format
      })
    });

    if (!response.ok) {
      throw new Error("Falha no processamento do servidor.");
    }

    const result = await response.json();

    if (result.status === "success" && result.fileUrl) {
      btnDownload.innerHTML = `<span>Baixando...</span> <i class="fa-solid fa-check"></i>`;
      window.location.href = result.fileUrl;
    } else {
      alert("Erro ao processar o arquivo.");
    }

  } catch (error) {
    console.error('Erro:', error);
    alert('Erro ao comunicar com o servidor.');
  } finally {
    btnDownload.innerHTML = `<span>Download</span> <i class="fa-solid fa-arrow-down-long"></i>`;
    btnDownload.disabled = false;
  }
}

document.getElementById('downloadForm').addEventListener('submit', function (event) {
  event.preventDefault();
  const url = document.getElementById('youtubeUrl').value;
  const format = document.getElementById('formatSelect').value;

  sendLinkToServer(url, format);
  document.getElementById('youtubeUrl').value = "";
});

// Botão de Colar do Clipboard
document.getElementById('pasteBtn').addEventListener('click', async () => {
  try {
    const text = await navigator.clipboard.readText();
    document.getElementById('youtubeUrl').value = text;
  } catch (err) {
    alert('Não foi possível acessar a área de transferência.');
  }
});

document.addEventListener("DOMContentLoaded", function () {
  const banner = document.getElementById("cookie-banner");
  const acceptBtn = document.getElementById("accept-cookies-btn");

  if (localStorage.getItem("cookiesAccepted") === "true") {
    banner.style.display = "none";
  }

  acceptBtn.addEventListener("click", function () {
    localStorage.setItem("cookiesAccepted", "true");
    banner.style.display = "none";
  });
});
