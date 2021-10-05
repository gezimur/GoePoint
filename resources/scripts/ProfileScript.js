	function editData()
	{
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
			Inputs[item].readOnly = false;
		
		Buttons = ButtonBlock.querySelectorAll("input");
		for (item  = 0; item < Buttons.length; item++)
		{
			if (Buttons[item].value == "Edit")
				Buttons[item].hidden = true;

			if (Buttons[item].value == "Cancel" || Buttons[item].value == "Save")
				Buttons[item].hidden = false;		
		}
	}
	function cancelEdit()
	{
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
			Inputs[item].readOnly = true;
		
		Buttons = ButtonBlock.querySelectorAll("input");
		for (item  = 0; item < Buttons.length; item++)
		{
			if (Buttons[item].value == "Edit")
				Buttons[item].hidden = false;

			if (Buttons[item].value == "Cancel" || Buttons[item].value == "Save")
				Buttons[item].hidden = true;
		}
	}
	
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
		
		if (bRewriteCustomer)
			form.append("rewrite_customer", "1");
		
		sendForm(form, printData, window.location.pathname + "/save");
	}
	
	cancelEdit();
	uploadData();