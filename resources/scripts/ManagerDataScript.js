    Statuses.innerHTML = "<option value=\"0\">Open</option>" +
						"<option value=\"3\">Close</option>";
	
	function editData()
	{
		Statuses.readOnly = false;
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
			if (Inputs[item].name != "executor")
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
		Statuses.readOnly = true;
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
			res = confirm("A customer with such a passport already exists, but does not correspond to the one sent.\n Do you want to rewrite it?");
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
	
	cancelEdit();
	uploadData();