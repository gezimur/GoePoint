	function sendForm(form, receiveFunc, url)
	{
		var req = new XMLHttpRequest();
		req.addEventListener('load', function(e)
		{
			var data = e.target;
			var response = data.responseText;
			receiveFunc(JSON.parse(response));
		});
		req.open('POST', url);
		req.responseType = 'text';
		req.send(form);
	}
	function createMyForm(message)
	{
		var form = new FormData();
		for (item  = 0; item < message.length; item++)
			if (message[item].value != "")
				form.append(message[item].name, message[item].value);

		return form;
	}
	function createMessage() 
	{
		return InputBlock.querySelectorAll("input");
	}

	function printData(Responce)
	{
		path = window.location.pathname;
		path = path.substr(path.lastIndexOf("/") + 1);
		if ("new" == path)
			Title.innerHTML = "РќРѕРІС‹Р№ Р·Р°РєР°Р·";
		else
			Title.innerHTML = "Р—Р°РєР°Р· РЅРѕРјРµСЂ " + path;
		
		if (Responce.message == undefined)
			Message.hidden = true;
		else
		{
			Message.hidden = false;
			Message.innerHTML = Responce.message;
		}
	
		Inputs = InputBlock.querySelectorAll("input");
		if (Responce.table == undefined)
			return;
		
		JsonTable = Responce.table[0];
		for (i = 0; i < Inputs.length; i++)
		{
			Inputs[i].value = JsonTable[Inputs[i].name];
		}
	}
	
	function loadDoc()
	{
		var FileName = DocList.value;
		window.open("/document/" + FileName);
	}
	
	function makeFileList(Responce)
	{
		path = window.location.pathname;
		path = path.substr(path.lastIndexOf("/") + 1);
		if ("new" == path || Responce.length < 0)
		{
			DocList.hidden = "true";
			LoadDoc.hidden = "true";
			return ;
		}
			
		DocList.hidden = "false";
		LoadDoc.hidden = "false";
		
		for (i = 0; i < Responce.length; i++)
		{
			Inputs[i].value = JsonTable[Inputs[i].name];
			var Option = document.createElement("option");
			Option.value = i;
			Option.innerHTML = Responce[i];
			DocList.append(Option);
		}
		
	}
	
	function uploadData()
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname);
		
		sendForm(new FormData(), makeFileList, "/doc_list");
	}
	
	function saveData(bRewriteCustomer = false)
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		if (bRewriteCustomer)
			form.append("rewrite_customer", "1");
		
		sendForm(form, tryToSave, window.location.pathname + "/save");
	}
	
	function tryToSave(Responce)
	{
		RespMsg = Responce.message;
		if ("rewrite_customer?" == RespMsg)
		{
			res = confirm("Р—Р°РєР°Р·С‡РёРє СЃ С‚Р°РєРёРј РЅРѕРјРµСЂРѕРј РїР°СЃСЃРїРѕСЂС‚Р° СѓР¶Рµ СЃСѓС‰РµСЃС‚РІСѓРµС‚.\n РџРµСЂРµР·Р°РїРёР°С‚СЊ РґР°РЅРЅС‹Рµ?");
			if (res)
			{
				saveData(true);
			}
		}
		else
		{
			Message.innerHTML = RespMsg;
		}
	}
	
	function setValFunc(select)
		{
			Status.value = select.value;
		}