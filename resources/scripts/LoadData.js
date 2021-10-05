	function printData(Responce)
	{
		Message.innerHTML = Responce.message;
	
		Inputs = InputBlock.querySelectorAll("input");	
		JsonTable = Responce.table[0];
		for (i = 0; i < Inputs.length; i++)
		{
			Inputs[i].value = JsonTable[Inputs[i].name];
		}
	}
	
	function uploadData()
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname);
	}
	
	function saveData()
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname + "/save");
	}
	
	uploadData();